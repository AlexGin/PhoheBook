CREATE TABLE pbk_records
(
    id serial PRIMARY KEY,
    name_first varchar(32) NOT NULL,
    name_second varchar(32) NULL,
    phone char(32) NOT NULL,
    email char(32) NULL 
)
