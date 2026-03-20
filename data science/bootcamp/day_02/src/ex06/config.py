NUM_OF_GEN_PAIRS: int = 3

FILE_PATH: str = ""
FILE_NAME: str = "report"
FILE_FORMAT: str = ".txt"

LOGGING_FILE: str = "analytics.log"

CHAT_ID: str = ""
BOT_TOKEN: str = ""
BASE_URL: str = "https://api.telegram.org/bot@TOKEN@/sendMessage"

REPORT_TEMPL: str = (
    "We have made @OBS@ observations from tossing a coin:"
    + " @TAILS@ of them were tails and @HEADS@ of them were heads."
    + " The probabilities are @HEADS_PERC@% and @TAILS_PERC@%, respectively."
    + " Our forecast is that in the next @GEN_OBS@ observations we will have:"
    + " @GEN_TAILS@ tail and @GEN_HEADS@ heads."
)
