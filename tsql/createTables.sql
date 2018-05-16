USE trackDay

DROP TABLE users
DROP TABLE userTypes

CREATE TABLE userTypes (
	id INT NOT NULL IDENTITY(1,1),
	type VARCHAR(32) NOT NULL,
	PRIMARY KEY(ID)
);

CREATE TABLE users (
	id INT NOT NULL IDENTITY(1,1),
	typeId INT NOT NULL,
	name VARCHAR(32) NOT NULL,
	passwordSha1 VARCHAR(40) NOT NULL,
	PRIMARY KEY(ID),
	FOREIGN KEY (typeId) REFERENCES userTypes(id)
);

INSERT INTO userTypes VALUES ('Racer');
INSERT INTO userTypes VALUES ('Cashier');
INSERT INTO userTypes VALUES ('Administrator');

INSERT INTO users
SELECT id, 'Zdzisek', 'b2bba6145b37e301dea598b4d23970ddc6e2f1a7'
FROM userTypes WHERE type = 'Racer';

SELECT * FROM userTypes
SELECT * FROM users

SELECT passwordSha1 FROM users WHERE typeId = 0 AND name = 'Zdzisek'