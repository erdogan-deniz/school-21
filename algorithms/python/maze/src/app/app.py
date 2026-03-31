"""Creates and launches the PyQt5 application."""

import ctypes
import sys

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QApplication

from utils.paths import ProjectPaths

from .widgets.main_window import MainWindow


class MazeApp:
    """Application class: initializes QApplication and the main window."""

    app: QApplication
    window: MainWindow

    def __init__(self) -> None:
        """Creates a QApplication instance and the MainWindow."""
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            "school21.maze"
        )
        self.app = QApplication(sys.argv)
        icon_path = ProjectPaths.get_assets_dir() / "icons" / "app.ico"
        if icon_path.exists():
            self.app.setWindowIcon(QIcon(str(icon_path)))
        self.app.setStyleSheet("""
            QGroupBox {
                border: 1px solid #222222;
                border-radius: 4px;
                margin-top: 6px;
                padding-top: 4px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 8px;
                color: #6B5040;
            }
            QPushButton {
                border: 1px solid #222222;
                border-radius: 4px;
                padding: 4px 10px;
                background-color: #EDE5D8;
            }
            QPushButton:hover {
                background-color: #DDD0BC;
            }
            QPushButton:pressed {
                background-color: #C8B89A;
            }
            QPushButton:disabled {
                border-color: #DDD0BC;
                color: #B0A090;
            }
            QSpinBox {
                border: 1px solid #222222;
                border-radius: 4px;
                padding: 2px 4px;
                background-color: #FFFDF9;
            }
            QTabWidget::pane {
                border: 1px solid #222222;
                border-radius: 4px;
            }
            QTabBar::tab {
                border: 1px solid #222222;
                border-bottom: none;
                border-radius: 4px 4px 0 0;
                padding: 4px 12px;
                background-color: #EDE5D8;
            }
            QTabBar::tab:selected {
                background-color: #FAF6F0;
            }
        """)
        self.window = MainWindow()

    def run(self) -> int:
        """Shows the main window and starts the Qt event loop.

        Returns:
            Application exit code returned by exec_().
        """
        self.window.show()
        return self.app.exec_()


if __name__ == "__main__":  # pragma: no cover
    app = MazeApp()
    sys.exit(app.run())
