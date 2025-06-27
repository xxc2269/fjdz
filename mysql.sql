CREATE DATABASE  IF NOT EXISTS game;
USE game;

CREATE USER IF NOT EXISTS 'manager' @'localhost' IDENTIFIED BY '123456';

CREATE TABLE IF NOT EXISTS users(
		ID INT PRIMARY KEY AUTO_INCREMENT,
        username VARCHAR(45) NOT NULL UNIQUE, 
        password VARCHAR(45) NOT NULL
);

CREATE TABLE IF NOT EXISTS record(
		ID INT PRIMARY KEY Auto_Increment,
        username VARCHAR(45),
        score INT
);

CREATE TABLE IF NOT EXISTS islogin(
		ID INT PRIMARY KEY,
        islogin INT,
        username VARCHAR(45)
);

GRANT SELECT, INSERT, UPDATE, DELETE ON game.* TO 'manager'@'localhost';