CREATE TABLE
  "users" (
    "id" INTEGER,
    "username" TEXT NOT NULL,
    "pwd" TEXT NOT NULL,
    PRIMARY KEY ("id" AUTOINCREMENT)
  );

CREATE TABLE
  "items" (
    "id" INTEGER,
    "name" TEXT NOT NULL,
    "amount" INTEGER,
    PRIMARY KEY ("id" AUTOINCREMENT)
  );

CREATE TABLE
  "cart" (
    "id" INTEGER,
    "user_id" INTEGER NOT NULL,
    "item_id" INTEGER NOT NULL,
    "item_amount" INTEGER NOT NULL,
    FOREIGN KEY ("user_id") REFERENCES "users" ("id"),
    FOREIGN KEY ("item_id") REFERENCES "items" ("id"),
    PRIMARY KEY ("id" AUTOINCREMENT)
  );
