"""Asynchronous image downloader — entry point."""

import asyncio

import aiohttp
from display import print_summary
from downloader import download_image
from validator import get_valid_save_dir


async def main() -> None:
    """Run the interactive image-download loop."""

    save_dir: str = await asyncio.to_thread(get_valid_save_dir)
    tasks: list[asyncio.Task[tuple[str, str]]] = []

    async with aiohttp.ClientSession() as session:
        while True:
            url: str = await asyncio.to_thread(input, "Enter image URL (empty line to stop): ")
            url = url.strip()

            if not url:
                break

            task: asyncio.Task[tuple[str, str]] = asyncio.create_task(
                download_image(session, url, save_dir)
            )

            tasks.append(task)

        pending: list[asyncio.Task[tuple[str, str]]] = [t for t in tasks if not t.done()]

        if pending:
            print(f"Waiting for {len(pending)} download(s) to finish...")

        results: list[tuple[str, str]] = list(await asyncio.gather(*tasks))

    print()
    print_summary(results)


if __name__ == "__main__":
    asyncio.run(main())
