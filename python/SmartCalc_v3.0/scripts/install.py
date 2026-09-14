"""Cross-platform application installer for SmartCalc v3.0.

Usage (via Makefile):
    make install-app

Direct usage:
    python scripts/install.py
"""

import shutil
import subprocess
import sys
from pathlib import Path


def _project_root() -> Path:
    """Return the project root (parent of scripts/)."""
    return Path(__file__).resolve().parent.parent


def _install_dir() -> Path:
    """Return the platform-appropriate installation directory."""
    if sys.platform == "darwin":
        return Path.home() / "Library" / "Application Support" / "SmartCalc"
    return Path.home() / ".local" / "share" / "SmartCalc"


def _compile_lib(project_root: Path) -> None:
    """Compile the C shared library via scripts/build_lib.py."""
    result = subprocess.run(
        [sys.executable, str(project_root / "scripts" / "build_lib.py")],
        check=False,
    )
    if result.returncode != 0:
        print("WARNING: Library compilation failed. Install may be incomplete.")


def _create_launcher(install_dir: Path) -> None:
    """Create a bash launcher script in the user's bin directory."""
    bin_dir = (
        Path.home() / "bin"
        if sys.platform == "darwin"
        else Path.home() / ".local" / "bin"
    )
    bin_dir.mkdir(parents=True, exist_ok=True)
    launcher = bin_dir / "smartcalc"
    launcher.write_text(
        "#!/usr/bin/env bash\n"
        f'exec "{sys.executable}" "{install_dir / "src" / "main.py"}" "$@"\n',
        encoding="utf-8",
    )
    launcher.chmod(0o755)
    print(f"Launcher     : {launcher}")


def _create_desktop_entry(install_dir: Path) -> None:
    """Create a .desktop shortcut (Linux only)."""
    if sys.platform != "linux":
        return
    apps_dir = Path.home() / ".local" / "share" / "applications"
    apps_dir.mkdir(parents=True, exist_ok=True)
    desktop = apps_dir / "smartcalc.desktop"
    desktop.write_text(
        "[Desktop Entry]\n"
        "Version=3.0\n"
        "Type=Application\n"
        "Name=SmartCalc v3.0\n"
        "Comment=Extended calculator with loan and deposit modes\n"
        f'Exec="{sys.executable}" "{install_dir / "src" / "main.py"}"\n'
        "Icon=accessories-calculator\n"
        "Terminal=false\n"
        "Categories=Utility;Calculator;\n",
        encoding="utf-8",
    )
    print(f"Desktop      : {desktop}")


def main() -> int:
    """Run the installer; return 0 on success.

    Returns:
        0 on success.

    """
    if sys.platform == "win32":
        print(
            "Windows installation: use the Inno Setup installer.\n"
            "  Build it with : make installer\n"
            "  Dev run       : make run"
        )
        return 0

    project_root = _project_root()
    install_dir = _install_dir()
    print(f"Installing SmartCalc v3.0 to {install_dir} ...")

    # 1. Copy src/
    src_dest = install_dir / "src"
    if src_dest.exists():
        shutil.rmtree(src_dest)
    shutil.copytree(project_root / "src", src_dest)
    print(f"Copied src/  : {src_dest}")

    # 2. Compile the C shared library
    _compile_lib(project_root)

    # 3. Install Python dependencies
    subprocess.run(
        [sys.executable, "-m", "pip", "install", "--user", str(project_root)],
        check=True,
    )

    # 4. Create launcher
    _create_launcher(install_dir)

    # 5. Create .desktop shortcut (Linux only)
    _create_desktop_entry(install_dir)

    print("\nDone. Run SmartCalc with: smartcalc")
    return 0


if __name__ == "__main__":
    sys.exit(main())
