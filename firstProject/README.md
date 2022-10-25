# t9search

This program finds a contact from a file when supplied file with contacts and a sequence of numbers.

## Compilation

Open the terminal or CMD and navigate to the file where is your program. Copy one of these commands.

## Usage

### For windows

```powershell
Get-Content {contact file name} | .\t9search {sequence of numbers}
```

### For linux

```git
./t9search < {filename} {sequence of numbers}
```

## Example of functionality

```powershell
Get-Content phoneNumberDB.txt | .\t9search 44
james, 604487344
kristina jelinkova, 776118448
igor svoboda, 720099410
danuse nemcova, 730177944
ladislava rihova, 739478341
antonin sedlacek, 736253449
```
