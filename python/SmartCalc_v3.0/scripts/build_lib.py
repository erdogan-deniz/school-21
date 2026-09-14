"""Cross-platform helper: compiles the C shared library.

On Windows uses MSVC (64-bit) discovered via vswhere.exe.
On Linux uses gcc; on macOS uses clang.
"""

import json
import locale
import os
import subprocess
import sys


# ---------------------------------------------------------------------------
# Toolchain discovery (Windows)
# ---------------------------------------------------------------------------


def _ver(name: str) -> tuple[int, ...]:
    """Parse a dotted version string into a tuple of ints for sorting.

    Returns:
        Tuple of ints parsed from the version string, or ``(0,)`` on error.

    """
    try:
        return tuple(int(x) for x in name.split("."))
    except ValueError:
        return (0,)


def _find_msvc() -> str:
    """Return the MSVC tools directory for the latest installed toolset.

    Returns:
        Absolute path to the versioned MSVC toolset directory.

    Raises:
        RuntimeError: If vswhere.exe is not found, no MSVC installation is
            detected, or the expected tools directory is missing.

    """
    vswhere = os.path.join(
        os.environ.get("PROGRAMFILES(X86)", r"C:\Program Files (x86)"),
        r"Microsoft Visual Studio\Installer\vswhere.exe",
    )
    if not os.path.exists(vswhere):
        raise RuntimeError(
            "vswhere.exe not found. Install Visual Studio Build Tools "
            "(https://aka.ms/buildtools)."
        )
    result = subprocess.run(
        [
            vswhere,
            "-latest",
            "-products",
            "*",
            "-requires",
            "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
            "-format",
            "json",
            "-utf8",
        ],
        capture_output=True,
        text=True,
        check=True,
    )
    installs = json.loads(result.stdout)
    if not installs:
        raise RuntimeError(
            "No MSVC installation with C++ tools found. "
            "Install 'MSVC v14x build tools' via the VS Installer."
        )
    install_path = installs[0]["installationPath"]
    tools_root = os.path.join(install_path, r"VC\Tools\MSVC")
    if not os.path.isdir(tools_root):
        raise RuntimeError(f"MSVC tools directory not found: {tools_root}")
    versions = sorted(os.listdir(tools_root), key=_ver, reverse=True)
    if not versions:
        raise RuntimeError(f"No toolset versions found in {tools_root}")
    return os.path.join(tools_root, versions[0])


def _find_winsdk() -> tuple[str, str]:
    """Return (sdk_root, sdk_version) for the latest installed Windows SDK.

    Returns:
        Tuple of ``(sdk_root, sdk_version)`` strings.

    Raises:
        RuntimeError: If the Windows SDK directory is not found or contains
            no versioned subdirectories.

    """
    sdk_root = os.path.join(
        os.environ.get("PROGRAMFILES(X86)", r"C:\Program Files (x86)"),
        r"Windows Kits\10",
    )
    include_root = os.path.join(sdk_root, "Include")
    if not os.path.isdir(include_root):
        raise RuntimeError(
            f"Windows SDK not found at {sdk_root}. "
            "Install Windows 10/11 SDK via the VS Installer."
        )
    versions = sorted(
        (v for v in os.listdir(include_root) if v.startswith("10.")),
        key=_ver,
        reverse=True,
    )
    if not versions:
        raise RuntimeError(f"No SDK versions found in {include_root}")
    return sdk_root, versions[0]


# ---------------------------------------------------------------------------
# C source location
# ---------------------------------------------------------------------------


def _find_c_src() -> str:
    """Return the path to the smart_calculator C sources.

    Tries, in order:
    1. SMARTCALC_C_SRC environment variable
    2. ../../c/SmartCalc_v1.0/src — the C core as it lives in the
       school-21 monorepo (this subproject sits at python/SmartCalc_v3.0)
    3. smart_calculator/src/ bundled inside this repo
    4. c_src/ subdirectory inside this repo (e.g. git submodule)

    Returns:
        Absolute path to the C source directory.

    Raises:
        RuntimeError: If no C source directory is found in any of the
            expected locations.

    """
    # scripts/ is one level below the project root
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    repo_root = os.path.dirname(os.path.dirname(project_root))
    candidates = [
        os.environ.get("SMARTCALC_C_SRC", ""),
        os.path.join(repo_root, "c", "SmartCalc_v1.0", "src"),
        os.path.join(project_root, "smart_calculator", "src"),
        os.path.join(project_root, "c_src"),
    ]
    for path in candidates:
        if path and os.path.isdir(path):
            return path
    raise RuntimeError(
        "C source directory not found. Set the SMARTCALC_C_SRC environment "
        "variable to the path of the SmartCalc_v1.0 src/ directory, or place "
        "the sources in smart_calculator/src/ or c_src/.\n"
        f"Tried: {[c for c in candidates if c]}"
    )


def _collect_sources(c_src: str) -> list[str]:
    """Return all .c files under c_src, skipping view/tests/qt_viewer.

    Returns:
        List of absolute paths to ``.c`` source files.

    Raises:
        RuntimeError: If no ``.c`` files are found under ``c_src``.

    """
    sources: list[str] = []
    for root, dirs, files in os.walk(c_src):
        dirs[:] = [d for d in dirs if d not in {"view", "tests", "qt_viewer"}]
        for f in files:
            if f.endswith(".c"):
                sources.append(os.path.join(root, f))
    if not sources:
        raise RuntimeError(f"No C source files found in {c_src}")
    return sources


# ---------------------------------------------------------------------------
# Platform-specific build
# ---------------------------------------------------------------------------


def _build_windows(c_src: str, out: str) -> None:
    """Compile libsmartcalc.dll using MSVC cl.exe.

    Raises:
        RuntimeError: If compilation fails (non-zero exit from cl.exe).

    """
    msvc_base = _find_msvc()
    sdk_root, sdk_ver = _find_winsdk()
    sources = _collect_sources(c_src)

    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    obj_dir = os.path.join(project_root, r"build\obj") + "\\"
    os.makedirs(obj_dir, exist_ok=True)
    os.makedirs(os.path.dirname(out), exist_ok=True)

    cl = os.path.join(msvc_base, r"bin\Hostx64\x64\cl.exe")
    env = os.environ.copy()
    env["INCLUDE"] = ";".join([
        os.path.join(msvc_base, "include"),
        os.path.join(sdk_root, "Include", sdk_ver, "ucrt"),
        os.path.join(sdk_root, "Include", sdk_ver, "shared"),
        os.path.join(sdk_root, "Include", sdk_ver, "um"),
    ])
    env["LIB"] = ";".join([
        os.path.join(msvc_base, r"lib\x64"),
        os.path.join(sdk_root, "Lib", sdk_ver, r"ucrt\x64"),
        os.path.join(sdk_root, "Lib", sdk_ver, r"um\x64"),
    ])
    env["PATH"] = (
        os.path.join(msvc_base, r"bin\Hostx64\x64") + ";" + env["PATH"]
    )

    cmd = [
        cl,
        "/LD",
        f"/Fe:{out}",
        f"/Fo{obj_dir}",
        "/D_USE_MATH_DEFINES",
        "/D_CRT_SECURE_NO_WARNINGS",
        f"/I{c_src}",
        *sources,
        "/link",
        "/EXPORT:s21_calculator",
        "/EXPORT:s21_loan_annuity",
        "/EXPORT:s21_loan_differentiated",
        "/EXPORT:s21_deposit",
        f"/IMPLIB:{obj_dir}libsmartcalc.lib",
    ]

    print(f"MSVC toolset : {msvc_base}")
    print(f"Windows SDK  : {sdk_root} ({sdk_ver})")
    print(f"C sources    : {c_src} ({len(sources)} files)")
    print(f"Output       : {out}")

    result = subprocess.run(
        cmd,
        env=env,
        capture_output=True,
        text=True,
        encoding=locale.getpreferredencoding(False) or "utf-8",
        errors="replace",
        check=False,
    )
    if result.returncode != 0:
        print(result.stdout[-2000:])
        raise RuntimeError(
            f"Compilation failed (exit code {result.returncode})"
        )
    print("Done.")


def _build_unix(c_src: str, out: str, compiler: str) -> None:
    """Compile the shared library using gcc (Linux) or clang (macOS).

    Raises:
        RuntimeError: If compilation fails (non-zero exit from the compiler).

    """
    sources = _collect_sources(c_src)
    os.makedirs(os.path.dirname(out), exist_ok=True)

    cmd = [
        compiler,
        "-shared",
        "-fPIC",
        "-std=c11",
        "-lm",
        f"-I{c_src}",
        *sources,
        "-o",
        out,
    ]

    print(f"Compiler     : {compiler}")
    print(f"C sources    : {c_src} ({len(sources)} files)")
    print(f"Output       : {out}")

    result = subprocess.run(cmd, capture_output=True, text=True, check=False)
    if result.returncode != 0:
        print(result.stderr[-2000:])
        raise RuntimeError(
            f"Compilation failed (exit code {result.returncode})"
        )
    print("Done.")


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------


def build() -> None:
    """Detect platform and compile the appropriate shared library."""
    c_src = _find_c_src()
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    if sys.platform == "win32":
        out = os.path.join(project_root, r"src\libs\libsmartcalc.dll")
        _build_windows(c_src, out)
    elif sys.platform == "darwin":
        out = os.path.join(project_root, "src/libs/libsmartcalc.dylib")
        _build_unix(c_src, out, "clang")
    else:
        out = os.path.join(project_root, "src/libs/libsmartcalc.so")
        _build_unix(c_src, out, "gcc")


if __name__ == "__main__":
    try:
        build()
    except RuntimeError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        sys.exit(1)
