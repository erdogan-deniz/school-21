"""Image download coroutine."""

import os
from urllib.parse import urlparse

import aiohttp


async def download_image(
    sess: aiohttp.ClientSession, url: str, save_dir: str
) -> tuple[str, str]:
    """
    Download a single image from *url* and save it to *save_dir*.

    :Parameters:
        sess (aiohttp.ClientSession): Shared :class:`aiohttp.ClientSession` used
            for the HTTP request.
        url (str): Absolute URL of the image to download.
        save_dir (str): Local directory where the image file will be written.

    :Returns:
        tuple[str, str]: A ``(url, status)`` tuple where *status* is
            ``"Success"`` on a successful download or ``"Error"`` if exception
            occurs.

    :Raises:
        Any exception raised during the download process is caught and handled
        by returning a ``(url, "Error")`` tuple.
    """

    try:
        parsed = urlparse(url)
        filename: str = os.path.basename(parsed.path) or "image"
        save_path: str = os.path.join(save_dir, filename)

        async with sess.get(url, timeout=aiohttp.ClientTimeout(total=30)) as resp:
            resp.raise_for_status()

            content: bytes = await resp.read()

        with open(save_path, "wb") as f:
            f.write(content)

        return (url, "Success")
    except Exception:
        return (url, "Error")
