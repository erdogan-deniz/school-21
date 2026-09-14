"""PyInstaller spec file for SmartCalc v3.0."""

import os


block_cipher = None

SRC = os.path.abspath("src")

a = Analysis(  # noqa: F821
    [os.path.join(SRC, "main.py")],
    pathex=[SRC],
    binaries=[
        (os.path.join(SRC, "libs", "libsmartcalc.dll"), "libs"),
    ],
    datas=[
        (os.path.join(SRC, "config.ini"), "."),
    ],
    hiddenimports=["PyQt6.sip"],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=["tkinter"],
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=block_cipher,
    noarchive=False,
)

pyz = PYZ(a.pure, a.zipped_data, cipher=block_cipher)  # noqa: F821

exe = EXE(  # noqa: F821
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name="SmartCalc",
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)

coll = COLLECT(  # noqa: F821
    exe,
    a.binaries,
    a.zipfiles,
    a.datas,
    strip=False,
    upx=True,
    upx_exclude=[],
    name="SmartCalc",
)
