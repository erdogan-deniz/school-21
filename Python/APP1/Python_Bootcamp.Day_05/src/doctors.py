import time  # Module for time freezing
import random  # For shuffle doctors
import threading  # Module for threats and mutex

locker = threading.Lock()  # Locker


class Doctor:
    def __init__(self, number: int = 0, screwdriver_left=None, screwdriver_right=None, status: str = "waiting"):
        self.number = number
        self.status = status
        self.screwdriver_left = screwdriver_left
        self.screwdriver_right = screwdriver_right
        self.threat = None

    def get_number(self):
        return self.number

    def get_status(self):
        return self.status

    def set_status(self, status: str):
        self.status = status

    def set_number(self, number: int):
        self.number = number

    def blast(self):
        if ((self.screwdriver_left.get_number() == self.get_number()) and
                (self.screwdriver_right.get_number() == self.get_number()) and
                (self.screwdriver_left.get_status() == "took") and (self.screwdriver_right.get_status() == "took")):
            print(f"Doctor {self.get_number()}: BLAST!")

            self.set_status("done")
            self.drop_left()
            self.drop_right()
            time.sleep(2)

    def take_right(self):
        self.screwdriver_right.set_status("took")
        self.screwdriver_right.set_number(self.get_number())
        time.sleep(1)

    def take_left(self):
        self.screwdriver_left.set_status("took")
        self.screwdriver_left.set_number(self.get_number())
        time.sleep(1)

    def drop_right(self):
        self.screwdriver_right.set_status("free")
        self.screwdriver_right.set_number(0)
        time.sleep(1)

    def drop_left(self):
        self.screwdriver_left.set_status("free")
        self.screwdriver_left.set_number(0)
        time.sleep(1)

    def process(self):  # Main function for threats
        while self.get_status() != "done":
            if self.screwdriver_left.get_status() == "free":
                self.take_left()

            if (self.get_number() == 13) and (self.screwdriver_left.get_status() == "took"):
                locker.acquire()
            elif self.screwdriver_right.get_status() == "free":
                self.take_right()

            if (self.get_number() == 9) and (self.screwdriver_left.get_status() == "free"):
                locker.release()

            if self.screwdriver_right.get_status() == "free":
                self.take_right()

            self.blast()

    def start(self):
        threading.Thread(target=self.process(), args=(1,)).start()


class Screwdriver:
    def __init__(self, status: str = "free", number: int = 0):
        self.status = status
        self.number = number

    def get_number(self):
        return self.number

    def get_status(self):
        return self.status

    def set_status(self, status: str):
        self.status = status

    def set_number(self, number: int):
        self.number = number


if __name__ == "__main__":
    # Create screwdrivers:
    screwdriver_one = Screwdriver()
    screwdriver_two = Screwdriver()
    screwdriver_three = Screwdriver()
    screwdriver_four = Screwdriver()
    screwdriver_five = Screwdriver()

    # Randomize doctors numbers:
    doctors = list(range(9, 14))
    random.shuffle(doctors)

    # At first, we take left and the second right:
    doctor_nine = Doctor(doctors[0], screwdriver_one, screwdriver_five)
    doctor_ten = Doctor(doctors[1], screwdriver_two, screwdriver_one)
    doctor_eleven = Doctor(doctors[2], screwdriver_three, screwdriver_two)
    doctor_twelve = Doctor(doctors[3], screwdriver_four, screwdriver_three)
    doctor_third = Doctor(doctors[4], screwdriver_five, screwdriver_four)

    # Launch threats:
    doctor_nine.start()
    doctor_ten.start()
    doctor_eleven.start()
    doctor_twelve.start()
    doctor_third.start()
