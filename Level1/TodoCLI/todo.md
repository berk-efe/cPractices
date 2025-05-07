# Run script

Clear screen.

```
TODO (with ascii art)

[ ] 1. ...
[ ] 2. ...
[ ] 3. ...
[ ] 4. ...
[ ] 5. ...
[ ] 6. ...


[1] Add new task.
[2] Remove existing task.
[3] Tick existing task.
[4] Remove existing tick.

[5] Help.
[6] Quit.

```

## [1] Add new task.
Clear screen.

> Check if there are 16 or more tasks.

```if no continue```

Get priorty ```(as int) (0 < n < 16) (if out of bounds reask)```

Get task ```(as str) (strlen max 64) (if too many chars reask)```

Return to main menu with ```"Task added"``` output.

## [2] Remove existing task.
Clear screen

> Check if there are any tasks

``` if yes continue ```

Get the id of the task. ``` (as int) (0 < n < tasklen) ```

Ask if they want to remove the task. ``` (y or [n]) ```

## [3] Tick existing task.
Clear screen

> Check if there are any "non-ticked" tasks

``` if yes continue ```

write a list of non-ticked tasks

Get the id of the task. ``` (as int) ```

## [4] Remove existing tick.
Clear screen

> Check if there are any "ticked" tasks

``` if yes continue ```

write a list of non-ticked tasks

Get the id of the task. ``` (as int) ```

## [5] Help.
Print the help text.

## [6] Quit.
Quit the program.


# Error Codes

### return 1: Unable to open file.
### return 2: Couldnt load the db.
### return 3: Allocation error.
### return 4: Couldnt create task.
### return 5: Too many tasks.
### return 6: Input error.
### return 7: Couldnt save db.
### return 8: Option out of range.
### return 9: Not enough tasks.