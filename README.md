# 🎵 CSCE 1102 - Music Playlist Manager

An application using C++ and Qt for managing and playing music playlists, developed for the **CSCE 1102 – Fundamentals of Computing 2 Lab** course project.

## Objective

The Music Playlist Manager simulates a real-world scenario where users can create, manage, and play music playlists efficiently. It incorporates advanced Object-Oriented Programming (OOP), data structures, file handling, algorithms, and UI design using Qt.

---

## Features

### 1. Login
- Login with username and password.
- Default admin account is created at the beginning.
- **Only the admin** can create and manage user accounts.

### 2. Admin Page
- **Admin Login** - Only the default admin account can access this page
- **Add/Delete users** - Create new users (username, password, email) and delete users.
- **Password validation** - Ensure passwords consists of 8 characters including numbers.
- **User Storage** - Store user data in files
- **View list of users** - Show a list of current users with an option to *delete accounts*, if needed.

### 3. User Dashboard
- **Personalized welcome message** with last played song.
- **Summary statistics**: total playlists created, recent playlists accessed.
- **Buttons** to create a new playlist, view playlists, search songs, and generate reports.

### 4. Playlist Management Page
- View all playlists in a table (Name, Number of Songs).
- Playlist records stored in files
- **Search functionality** (search playlists/songs by title)
- **Edit playlist details** (e.g., add/delete songs, rename playlist)

### 5. Playlist Creation Page
- Input form to create new playlists
  - Enter playlist name (*must be* ***unique***)
  - Add songs to the playlist by *selecting from the existing library*
- Error handling for invalid inputs (e.g., *empty playlists, unnamed playlists, duplicate playist names*)
- Playlist details stored in `.txt` files

### 6. Song Creation Page
- Input form to add new songs, requires:
  - Song title
  - Artist
  - Album
- Error handling for invalid inputs (e.g., *duplicate songs, empty fields*)

### 7. Reports Page
- Generate user-specific **playlist usage reports** with information such as
  - Total playlists created by user
  - Most played songs
- **Export reports** to `.txt` or `.csv` files.

---

## User Roles

- **Admin:** Full access to user and playlist management (username: admin, password: admin123).
- **User:** Manage own playlists and generate personal reports(create a user from the admin page).

---

## File Structure

> *(To be filled out once project structure is finalized.)*

---

## Setup Instructions

To set up and run the project locally:

### Necessary Dependencies

- Qt Creator
- C++ Compiler (e.g., g++)
- Git

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/your-username/music-playlist-manager.git
   cd music-playlist-manager
   ```

2. **Open the Project in Qt Creator**

   - Launch **Qt Creator**.
   - Go to **File → Open File or Project**.
   - Navigate to the project directory and open the `.pro` file.

3. **Build the Project**

   - Ensure your Qt kit and compiler are configured.
   - Click the **Build** button or press `Ctrl + B`.

4. **Run the Application**

   - Press the **Run** button or use `Ctrl + R`.

5. **Login with Default Admin**

   - Use the default admin credentials (set in the code) to log in.
   - From the admin dashboard, you can create additional user accounts.

---

## Sample Screenshots

> *(Screenshots of the login page, dashboard, playlist manager, etc. will be pasted here once implemented.)*

---


## Authors
- David Boules
- Hazem Ajlan
- Zeiad Mohamed
- Ali Gawad

---

## License

This project is for academic purposes only.
