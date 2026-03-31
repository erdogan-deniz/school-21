"""Application entry point. Configures logging and launches the GUI."""

import logging
import sys

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s %(name)s %(levelname)s %(message)s",
)
logger: logging.Logger = logging.getLogger(__name__)


def main() -> int:
    """Initialises and runs the MazeApp application.

    Returns:
        Process exit code: 0 on success, 1 on a critical error.
    """
    from app.app import MazeApp

    try:
        app = MazeApp()
        logger.info("Run application.")
        return app.run()
    except Exception as e:
        logger.critical(f"Can not run app: {e}")
        return 1


if __name__ == "__main__":  # pragma: no cover
    exit_code = main()
    sys.exit(exit_code)
