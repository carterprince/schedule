# schedule

A simple and fast way to print the time remaining until a given event in your routine.

## Installation

```
git clone https://github.com/carterprince/schedule
cd schedule
sudo make clean install
```

## Usage

```
schedule
```

When run, reads `$HOME/.config/schedule.cfg`, which should take the following format:

```
8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3

8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3

8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3

8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3

8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3

8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3

8:30:00:Wake up
9:00:00:Breakfast
11:30:00:Task 1
12:30:00:Task 2
13:30:00:Task 3
```

Each block represents one day. The first block is Monday, and the last one is Sunday.

If there are no other events today and the next event happens tomorrow, `schedule` will automatically calculate the remaining time.

`schedule` is perfect for those who want a simple routine timer that will not take up a lot of resources when running in a status bar.
