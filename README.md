![Pineapple](https://socialify.git.ci/CongJyu/Pineapple/image?description=1&font=Bitter&forks=1&issues=1&language=1&name=1&owner=1&pattern=Brick%20Wall&pulls=1&stargazers=1&theme=Light)

# Pineapple

A library management CLI

This is a COMMAND LINE TOOL, final-term project of the C++ Language Programming Course, CSEE, HNU.

All Rights Reserved. Rain Chen 2021.

## Basic functions

This is a simple CLI that can help you check your books list stored on your disk, manage users, and record logs. Just like a simple library.

## Usage

### Set your data dir

Follow the tips, enter your data dir. This folder will be used to store all the information about this library, so please put your library's booklist(for example: `books.txt`) in it as well.

The data dir must be like this: `/Users/rainchen/Documents/digiLibrary`.

### Log As Super User Mode (SU, also Administrator, root)

Press the `s` key on your keyboard, then `⏎Enter`. Then you will be required to enter your username and password. The default username for administrator is `admin`, and password `123456`.

### Log As Normal User Mode (For our teachers and students)

Press the `n` key on your keyboard, then `⏎Enter`. Then you will be required to enter your username(usually your School Number), as well as your password. Your account will be setup by Administrator so that you can only change your password. Username changes are not available.

### Help Command

Type like this, for both Administrator and Normal Users.

```shell
help
```

This command will show you all the commands available.

### Version Command

Type like this, for both Administrator and Normal Users.

```shell
version
```

This will show you the information about this software, including name of the software, version, authors and contributors.

### Emergency situations

If you find something go wrong, press `⌃Control` + `C` to terminate the session.

## Updates

### 2022-01-03

New version.

- Add a function so that you can search a certain type of books.
- Fixed some bugs.

### 2022-01-01

New version. Rebuilt whole project.

- Rebuilt this CLI with OOP methods.
- Make the CLI smaller and faster.

### 2021-12-27

New version. Fixed some bugs.

- We rebuilt this CLI.
- Now this source code is available for both macOS and Linux.
- You can't run it on Linux yet.

### 2021-12-19

New version. Fixed some bugs.

- Test Linux version.
- Add Windows version. Not build yet.

### 2021-12-18

Add new functions.

- Administrator can delete books from library now.
- Administrator can delete user accounts from usergroup now.
- Users can borrow and return books.
- Administrator can monitor the booklist of a specific individual.

Fixed some bugs.

- Now it can read and write a file normally.
- User profiles works.

### 2021-12-17

Change the color of LIBRARY title. Add colorful tips and hints to messages. Also, syntax highlighting is added.

### 2021-12-16

Fixed some bugs.

- The searching function don't sometimes break down anymore.
- The list of books is normal now.

### 2021-12-15

Now the books can be added nearly without limitations.

- The storage of the books can enlarge up to 10 thousands.
- The number of the users can enlarge up to 5 thousands.

### 2021-12-14

Add search function.

- You can search book names, authors, ISBN/ISSN now.
- You don't need to type the entire name of the book.

### 2021-12-13

Create this project.

## Supported OS

### macOS

Build succeeded.

### Linux

Not build yet.

### Windows

Build succeeded.

## Thanks

The Windows version of this Library-CLI is modified by [DavidKwan](https://github.com/DavidKwan3106).
