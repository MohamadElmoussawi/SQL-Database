#pragma once
/*

-----ALL RESULTS HAVE BEEN VERIFIED-----
-----BATCH FILE WITH > 100 Cases from canvas running-----
Available Tables:
> batch select.txt
[0]batch select.txt
//****************************************************************************
//              CREATE TABLES AND INSERT RECORDS
//****************************************************************************


[0]make table employee fields  last,            first,                  dep,            salary,         year

sql::run_command: create table last, first, dep, salary, year,
Table employee created. fields last, first, dep, salary, year,
[1]insert into employee values Blow,            Joe,                    CS,                     100000,         2018

Inserted into table: employee

[2]insert into employee values Blow,            JoAnn,                  Physics,        200000,         2016

Inserted into table: employee

[3]insert into employee values Johnson,         Jack,                   HR,             150000,         2014

Inserted into table: employee

[4]insert into employee values Johnson,         "Jimmy",                Chemistry,      140000,         2018

Inserted into table: employee

[5]insert into employee values Yao,             Jimmy,                  Math,           145000,         2014

Inserted into table: employee

[6]insert into employee values "Yao",           Flo,                    CS,                     147000,         2012

Inserted into table: employee

[7]insert into employee values Yang,            Bo,                     CS,                     160000,         2013

Inserted into table: employee

[8]insert into employee values Jackson, "Flo",                  Math,           165000,         2017

Inserted into table: employee

[9]insert into employee values Jackson, Bo,                             Chemistry,      130000,         2011

Inserted into table: employee

[10]insert into employee values "Jackson",      Billy,                  Math,           170000,         2017

Inserted into table: employee

[11]insert into employee values Johnson,        "Mary Ann",     Math,           165000,         2014

Inserted into table: employee

[12]insert into employee values Johnson,        "Billy Bob",    Physics,        142000,         2014

Inserted into table: employee

[13]insert into employee values Johnson,        Billy,                  "Phys Ed",      102000,         2014

Inserted into table: employee

[14]insert into employee values "Van Gogh",     Vincent,                Art,            240000,         2015

Inserted into table: employee

[15]insert into employee values "Van Gogh",     Vincent,                CS,                     245000,         2015

Inserted into table: employee

[16]insert into employee values "Van Gogh",     "Jim Bob",              "Phys Ed",      230000,         2010

Inserted into table: employee

[17]select * from employee

Table: employee_1 Total Records: 16

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson            Jack              HR          150000            2014
     3         Johnson           Jimmy       Chemistry          140000            2018
     4             Yao           Jimmy            Math          145000            2014
     5             Yao             Flo              CS          147000            2012
     6            Yang              Bo              CS          160000            2013
     7         Jackson             Flo            Math          165000            2017
     8         Jackson              Bo       Chemistry          130000            2011
     9         Jackson           Billy            Math          170000            2017
    10         Johnson        Mary Ann            Math          165000            2014
    11         Johnson       Billy Bob         Physics          142000            2014
    12         Johnson           Billy         Phys Ed          102000            2014
    13        Van Gogh         Vincent             Art          240000            2015
    14        Van Gogh         Vincent              CS          245000            2015
    15        Van Gogh         Jim Bob         Phys Ed          230000            2010

[18]make table student fields fname, lname, major, age, company

sql::run_command: create table fname, lname, major, age, company,
Table student created. fields fname, lname, major, age, company,
[19]insert into student values Flo,                     Yao,            CS,                             20,     Google

Inserted into table: student

[20]insert into student values Bo,                              Yang,           CS,                             28,
Microsoft

Inserted into table: student

[21]insert into student values "Sammuel L.",    Jackson,        CS,                             40,             Uber

Inserted into table: student

[22]insert into student values "Flo",                   "Jackson",      Math,                           21,            Google

Inserted into table: student

[23]insert into student values "Greg",                  "Pearson",      Physics,                        20,            Amazon

Inserted into table: student

[24]insert into student values "Jim Bob",               Smith,          Math,                           23,            Verizon

Inserted into table: student

[25]insert into student values Calvin,                  Woo,            Physics,                        22,            Uber

Inserted into table: student

[26]insert into student values "Anna Grace",    "Del Rio",      CS,                                     22,            USAF

Inserted into table: student

[27]insert into student values "Teresa Mae",    Gowers,         Chemistry,                      22,             Verizon

Inserted into table: student

[28]insert into student values Alex,                    Smith,          "Gender Studies",       53,             Amazon

Inserted into table: student

[29]select * from student

Table: student_1 Total Records: 10

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2      Sammuel L.         Jackson              CS              40            Uber
     3             Flo         Jackson            Math              21          Google
     4            Greg         Pearson         Physics              20          Amazon
     5         Jim Bob           Smith            Math              23         Verizon
     6          Calvin             Woo         Physics              22            Uber
     7      Anna Grace         Del Rio              CS              22            USAF
     8      Teresa Mae          Gowers       Chemistry              22         Verizon
     9            Alex           Smith  Gender Studies              53          Amazon



//****************************************************************************
//              SIMPLE SELECT:
//****************************************************************************

[30]select * from student

Table: student_2 Total Records: 10

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2      Sammuel L.         Jackson              CS              40            Uber
     3             Flo         Jackson            Math              21          Google
     4            Greg         Pearson         Physics              20          Amazon
     5         Jim Bob           Smith            Math              23         Verizon
     6          Calvin             Woo         Physics              22            Uber
     7      Anna Grace         Del Rio              CS              22            USAF
     8      Teresa Mae          Gowers       Chemistry              22         Verizon
     9            Alex           Smith  Gender Studies              53          Amazon


//------- simple strings -------------------
[31]select * from student where lname = Jackson

Table: student_2 Total Records: 2

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1             Flo         Jackson            Math              21          Google

[32]select * from student where major = CS

Table: student_3 Total Records: 4

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2      Sammuel L.         Jackson              CS              40            Uber
     3      Anna Grace         Del Rio              CS              22            USAF

[33]select * from student where company = Uber

Table: student_4 Total Records: 2

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1          Calvin             Woo         Physics              22            Uber


//----- quoted strings ---------------------
[34]select * from student where lname = "Del Rio"

Table: student_5 Total Records: 1

Record           fname           lname           major             age         company

     0      Anna Grace         Del Rio              CS              22            USAF

[35]select * from student where fname = "Jim Bob"

Table: student_6 Total Records: 1

Record           fname           lname           major             age         company

     0         Jim Bob           Smith            Math              23         Verizon

[36]select * from student where fname = "Anna Grace"

Table: student_7 Total Records: 1

Record           fname           lname           major             age         company

     0      Anna Grace         Del Rio              CS              22            USAF

[37]select * from student where fname = "Teresa Mae"

Table: student_8 Total Records: 1

Record           fname           lname           major             age         company

     0      Teresa Mae          Gowers       Chemistry              22         Verizon


//-------- non-existing string ------------------
[38]select * from student where lname = "Does Not Exist"

Table: student_9 Total Records: 0

Record           fname           lname           major             age         company



//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[39]select * from student where lname > Yang

Table: student_10 Total Records: 1

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google

[40]select * from student where major > Math

Table: student_11 Total Records: 2

Record           fname           lname           major             age         company

     0            Greg         Pearson         Physics              20          Amazon
     1          Calvin             Woo         Physics              22            Uber

[41]select * from student where fname > "Sammuel L."

Table: student_12 Total Records: 1

Record           fname           lname           major             age         company

     0      Teresa Mae          Gowers       Chemistry              22         Verizon

[42]select * from employee where salary > 200000

Table: employee_1 Total Records: 3

Record            last           first             dep          salary            year

     0        Van Gogh         Vincent             Art          240000            2015
     1        Van Gogh         Vincent              CS          245000            2015
     2        Van Gogh         Jim Bob         Phys Ed          230000            2010

[43]select * from employee where dep > Chemistry

Table: employee_2 Total Records: 9

Record            last           first             dep          salary            year

     0            Blow           JoAnn         Physics          200000            2016
     1         Johnson            Jack              HR          150000            2014
     2             Yao           Jimmy            Math          145000            2014
     3         Jackson             Flo            Math          165000            2017
     4         Jackson           Billy            Math          170000            2017
     5         Johnson        Mary Ann            Math          165000            2014
     6         Johnson       Billy Bob         Physics          142000            2014
     7         Johnson           Billy         Phys Ed          102000            2014
     8        Van Gogh         Jim Bob         Phys Ed          230000            2010

[44]select * from employee where last > Jackson

Table: employee_3 Total Records: 11

Record            last           first             dep          salary            year

     0         Johnson            Jack              HR          150000            2014
     1         Johnson           Jimmy       Chemistry          140000            2018
     2             Yao           Jimmy            Math          145000            2014
     3             Yao             Flo              CS          147000            2012
     4            Yang              Bo              CS          160000            2013
     5         Johnson        Mary Ann            Math          165000            2014
     6         Johnson       Billy Bob         Physics          142000            2014
     7         Johnson           Billy         Phys Ed          102000            2014
     8        Van Gogh         Vincent             Art          240000            2015
     9        Van Gogh         Vincent              CS          245000            2015
    10        Van Gogh         Jim Bob         Phys Ed          230000            2010

[45]select * from employee where first > "Billy Bob"

Table: employee_4 Total Records: 13

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson            Jack              HR          150000            2014
     3         Johnson           Jimmy       Chemistry          140000            2018
     4             Yao           Jimmy            Math          145000            2014
     5             Yao             Flo              CS          147000            2012
     6            Yang              Bo              CS          160000            2013
     7         Jackson             Flo            Math          165000            2017
     8         Jackson              Bo       Chemistry          130000            2011
     9         Johnson        Mary Ann            Math          165000            2014
    10        Van Gogh         Vincent             Art          240000            2015
    11        Van Gogh         Vincent              CS          245000            2015
    12        Van Gogh         Jim Bob         Phys Ed          230000            2010



//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[46]select * from student where age > 50

Table: student_13 Total Records: 1

Record           fname           lname           major             age         company

     0            Alex           Smith  Gender Studies              53          Amazon

[47]select * from student where age > 35

Table: student_14 Total Records: 2

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1            Alex           Smith  Gender Studies              53          Amazon

[48]select * from student where fname > T

Table: student_15 Total Records: 1

Record           fname           lname           major             age         company

     0      Teresa Mae          Gowers       Chemistry              22         Verizon

[49]select * from employee where salary > 130000

Table: employee_5 Total Records: 13

Record            last           first             dep          salary            year

     0            Blow           JoAnn         Physics          200000            2016
     1         Johnson            Jack              HR          150000            2014
     2         Johnson           Jimmy       Chemistry          140000            2018
     3             Yao           Jimmy            Math          145000            2014
     4             Yao             Flo              CS          147000            2012
     5            Yang              Bo              CS          160000            2013
     6         Jackson             Flo            Math          165000            2017
     7         Jackson           Billy            Math          170000            2017
     8         Johnson        Mary Ann            Math          165000            2014
     9         Johnson       Billy Bob         Physics          142000            2014
    10        Van Gogh         Vincent             Art          240000            2015
    11        Van Gogh         Vincent              CS          245000            2015
    12        Van Gogh         Jim Bob         Phys Ed          230000            2010

[50]select * from employee where  year > 2009

Table: employee_6 Total Records: 16

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson            Jack              HR          150000            2014
     3         Johnson           Jimmy       Chemistry          140000            2018
     4             Yao           Jimmy            Math          145000            2014
     5             Yao             Flo              CS          147000            2012
     6            Yang              Bo              CS          160000            2013
     7         Jackson             Flo            Math          165000            2017
     8         Jackson              Bo       Chemistry          130000            2011
     9         Jackson           Billy            Math          170000            2017
    10         Johnson        Mary Ann            Math          165000            2014
    11         Johnson       Billy Bob         Physics          142000            2014
    12         Johnson           Billy         Phys Ed          102000            2014
    13        Van Gogh         Vincent             Art          240000            2015
    14        Van Gogh         Vincent              CS          245000            2015
    15        Van Gogh         Jim Bob         Phys Ed          230000            2010


//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[51]select * from student where age  > 53

Table: student_16 Total Records: 0

Record           fname           lname           major             age         company


[52]select * from student where lname > Yao

Table: student_17 Total Records: 0

Record           fname           lname           major             age         company


[53]select * from student where fname > "Teresa Mae"

Table: student_18 Total Records: 0

Record           fname           lname           major             age         company


[54]select * from employee where last > "Van Gogh"

Table: employee_7 Total Records: 3

Record            last           first             dep          salary            year

     0             Yao           Jimmy            Math          145000            2014
     1             Yao             Flo              CS          147000            2012
     2            Yang              Bo              CS          160000            2013

[55]select * from employee where first > Vincent

Table: employee_8 Total Records: 0

Record            last           first             dep          salary            year


[56]select * from employee where salary > 260000

Table: employee_9 Total Records: 0

Record            last           first             dep          salary            year



//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[57]select * from student where age > 54

Table: student_19 Total Records: 0

Record           fname           lname           major             age         company


[58]select * from student where lname > Zoolander

Table: student_20 Total Records: 0

Record           fname           lname           major             age         company


[59]select * from employee where last > Zoolaner

Table: employee_10 Total Records: 0

Record            last           first             dep          salary            year


[60]select * from employee where first > Xu

Table: employee_11 Total Records: 0

Record            last           first             dep          salary            year



//.................
//:Greater Equal  :
//.................
[61]select * from student where lname >= Yang

Table: student_21 Total Records: 2

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft

[62]select * from student where fname >= "Sammuel L."

Table: student_22 Total Records: 2

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1      Teresa Mae          Gowers       Chemistry              22         Verizon

[63]select * from student where age >= 40

Table: student_23 Total Records: 2

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1            Alex           Smith  Gender Studies              53          Amazon

//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[64]select * from employee where last >= Jack

Table: employee_12 Total Records: 14

Record            last           first             dep          salary            year

     0         Johnson            Jack              HR          150000            2014
     1         Johnson           Jimmy       Chemistry          140000            2018
     2             Yao           Jimmy            Math          145000            2014
     3             Yao             Flo              CS          147000            2012
     4            Yang              Bo              CS          160000            2013
     5         Jackson             Flo            Math          165000            2017
     6         Jackson              Bo       Chemistry          130000            2011
     7         Jackson           Billy            Math          170000            2017
     8         Johnson        Mary Ann            Math          165000            2014
     9         Johnson       Billy Bob         Physics          142000            2014
    10         Johnson           Billy         Phys Ed          102000            2014
    11        Van Gogh         Vincent             Art          240000            2015
    12        Van Gogh         Vincent              CS          245000            2015
    13        Van Gogh         Jim Bob         Phys Ed          230000            2010

[65]select * from employee where first >= Bill

Table: employee_13 Total Records: 16

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson            Jack              HR          150000            2014
     3         Johnson           Jimmy       Chemistry          140000            2018
     4             Yao           Jimmy            Math          145000            2014
     5             Yao             Flo              CS          147000            2012
     6            Yang              Bo              CS          160000            2013
     7         Jackson             Flo            Math          165000            2017
     8         Jackson              Bo       Chemistry          130000            2011
     9         Jackson           Billy            Math          170000            2017
    10         Johnson        Mary Ann            Math          165000            2014
    11         Johnson       Billy Bob         Physics          142000            2014
    12         Johnson           Billy         Phys Ed          102000            2014
    13        Van Gogh         Vincent             Art          240000            2015
    14        Van Gogh         Vincent              CS          245000            2015
    15        Van Gogh         Jim Bob         Phys Ed          230000            2010

[66]select * from employee where salary >= 235000

Table: employee_14 Total Records: 2

Record            last           first             dep          salary            year

     0        Van Gogh         Vincent             Art          240000            2015
     1        Van Gogh         Vincent              CS          245000            2015



//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[67]select * from student where lname < Jackson

Table: student_24 Total Records: 2

Record           fname           lname           major             age         company

     0      Anna Grace         Del Rio              CS              22            USAF
     1      Teresa Mae          Gowers       Chemistry              22         Verizon

[68]select * from student where major < Math

Table: student_25 Total Records: 6

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2      Sammuel L.         Jackson              CS              40            Uber
     3      Anna Grace         Del Rio              CS              22            USAF
     4      Teresa Mae          Gowers       Chemistry              22         Verizon
     5            Alex           Smith  Gender Studies              53          Amazon

[69]select * from student where fname < "Jim Bob"

Table: student_26 Total Records: 7

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2             Flo         Jackson            Math              21          Google
     3            Greg         Pearson         Physics              20          Amazon
     4          Calvin             Woo         Physics              22            Uber
     5      Anna Grace         Del Rio              CS              22            USAF
     6            Alex           Smith  Gender Studies              53          Amazon

[70]select * from employee where salary < 200000

Table: employee_15 Total Records: 12

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1         Johnson            Jack              HR          150000            2014
     2         Johnson           Jimmy       Chemistry          140000            2018
     3             Yao           Jimmy            Math          145000            2014
     4             Yao             Flo              CS          147000            2012
     5            Yang              Bo              CS          160000            2013
     6         Jackson             Flo            Math          165000            2017
     7         Jackson              Bo       Chemistry          130000            2011
     8         Jackson           Billy            Math          170000            2017
     9         Johnson        Mary Ann            Math          165000            2014
    10         Johnson       Billy Bob         Physics          142000            2014
    11         Johnson           Billy         Phys Ed          102000            2014

[71]select * from employee where dep < CS

Table: employee_16 Total Records: 1

Record            last           first             dep          salary            year

     0        Van Gogh         Vincent             Art          240000            2015

[72]select * from employee where last < Jackson

Table: employee_17 Total Records: 2

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016

[73]select * from employee where first < "Billy Bob"

Table: employee_18 Total Records: 2

Record            last           first             dep          salary            year

     0         Jackson           Billy            Math          170000            2017
     1         Johnson           Billy         Phys Ed          102000            2014


//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[74]select * from student where age  < 20

Table: student_27 Total Records: 0

Record           fname           lname           major             age         company


[75]select * from student where lname < "Del Rio"

Table: student_28 Total Records: 0

Record           fname           lname           major             age         company


[76]select * from student where fname < Alex

Table: student_29 Total Records: 0

Record           fname           lname           major             age         company


[77]select * from employee where last < Blow

Table: employee_19 Total Records: 0

Record            last           first             dep          salary            year


[78]select * from employee where first < Billy

Table: employee_20 Total Records: 0

Record            last           first             dep          salary            year


[79]select * from employee where salary < 100000

Table: employee_21 Total Records: 0

Record            last           first             dep          salary            year




//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[80]select * from student where age  < 19

Table: student_30 Total Records: 0

Record           fname           lname           major             age         company


[81]select * from student where lname < Adams

Table: student_31 Total Records: 0

Record           fname           lname           major             age         company


[82]select * from student where fname < Adam

Table: student_32 Total Records: 0

Record           fname           lname           major             age         company


[83]select * from employee where last < Alex

Table: employee_22 Total Records: 0

Record            last           first             dep          salary            year


[84]select * from employee where first < Avory

Table: employee_23 Total Records: 0

Record            last           first             dep          salary            year


[85]select * from employee where dep < Alchemy

Table: employee_24 Total Records: 0

Record            last           first             dep          salary            year




//.................
//:Less Equal     :
//.................

[86]select * from student where lname <= Smith

Table: student_33 Total Records: 7

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1             Flo         Jackson            Math              21          Google
     2            Greg         Pearson         Physics              20          Amazon
     3         Jim Bob           Smith            Math              23         Verizon
     4      Anna Grace         Del Rio              CS              22            USAF
     5      Teresa Mae          Gowers       Chemistry              22         Verizon
     6            Alex           Smith  Gender Studies              53          Amazon

[87]select * from student where fname <= Greg

Table: student_34 Total Records: 7

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2             Flo         Jackson            Math              21          Google
     3            Greg         Pearson         Physics              20          Amazon
     4          Calvin             Woo         Physics              22            Uber
     5      Anna Grace         Del Rio              CS              22            USAF
     6            Alex           Smith  Gender Studies              53          Amazon

[88]select * from student where age <= 40

Table: student_35 Total Records: 9

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2      Sammuel L.         Jackson              CS              40            Uber
     3             Flo         Jackson            Math              21          Google
     4            Greg         Pearson         Physics              20          Amazon
     5         Jim Bob           Smith            Math              23         Verizon
     6          Calvin             Woo         Physics              22            Uber
     7      Anna Grace         Del Rio              CS              22            USAF
     8      Teresa Mae          Gowers       Chemistry              22         Verizon


//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[89]select * from employee where last <= Peach

Table: employee_25 Total Records: 10

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson            Jack              HR          150000            2014
     3         Johnson           Jimmy       Chemistry          140000            2018
     4         Jackson             Flo            Math          165000            2017
     5         Jackson              Bo       Chemistry          130000            2011
     6         Jackson           Billy            Math          170000            2017
     7         Johnson        Mary Ann            Math          165000            2014
     8         Johnson       Billy Bob         Physics          142000            2014
     9         Johnson           Billy         Phys Ed          102000            2014

[90]select * from employee where first <= Gary

Table: employee_26 Total Records: 7

Record            last           first             dep          salary            year

     0             Yao             Flo              CS          147000            2012
     1            Yang              Bo              CS          160000            2013
     2         Jackson             Flo            Math          165000            2017
     3         Jackson              Bo       Chemistry          130000            2011
     4         Jackson           Billy            Math          170000            2017
     5         Johnson       Billy Bob         Physics          142000            2014
     6         Johnson           Billy         Phys Ed          102000            2014

[91]select * from employee where salary <= 23500

Table: employee_27 Total Records: 14

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson            Jack              HR          150000            2014
     3         Johnson           Jimmy       Chemistry          140000            2018
     4             Yao           Jimmy            Math          145000            2014
     5             Yao             Flo              CS          147000            2012
     6            Yang              Bo              CS          160000            2013
     7         Jackson             Flo            Math          165000            2017
     8         Jackson              Bo       Chemistry          130000            2011
     9         Jackson           Billy            Math          170000            2017
    10         Johnson        Mary Ann            Math          165000            2014
    11         Johnson       Billy Bob         Physics          142000            2014
    12         Johnson           Billy         Phys Ed          102000            2014
    13        Van Gogh         Jim Bob         Phys Ed          230000            2010


//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[92]select * from student where fname = "Flo" and lname = "Yao"

Table: student_36 Total Records: 1

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google

[93]select * from student where major = "CS" and age < 25

Table: student_37 Total Records: 2

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1      Anna Grace         Del Rio              CS              22            USAF

[94]select * from student where major < Math and age > 25

Table: student_38 Total Records: 3

Record           fname           lname           major             age         company

     0              Bo            Yang              CS              28       Microsoft
     1      Sammuel L.         Jackson              CS              40            Uber
     2            Alex           Smith  Gender Studies              53          Amazon

[95]select * from employee where dep = CS and salary > 150000

Table: employee_28 Total Records: 2

Record            last           first             dep          salary            year

     0            Yang              Bo              CS          160000            2013
     1        Van Gogh         Vincent              CS          245000            2015

[96]select * from employee where last = Jackson and year < 2015

Table: employee_29 Total Records: 1

Record            last           first             dep          salary            year

     0         Jackson              Bo       Chemistry          130000            2011

[97]select * from employee where last = Johnson and year >=2014

Table: employee_30 Total Records: 5

Record            last           first             dep          salary            year

     0         Johnson            Jack              HR          150000            2014
     1         Johnson           Jimmy       Chemistry          140000            2018
     2         Johnson        Mary Ann            Math          165000            2014
     3         Johnson       Billy Bob         Physics          142000            2014
     4         Johnson           Billy         Phys Ed          102000            2014



//.................
//:OR            :
//.................
[98]select * from student where fname = Flo or lname = Jackson

Table: student_39 Total Records: 3

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1      Sammuel L.         Jackson              CS              40            Uber
     2             Flo         Jackson            Math              21          Google

[99]select * from student where age >=40  or company = Verizon

Table: student_40 Total Records: 4

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1         Jim Bob           Smith            Math              23         Verizon
     2      Teresa Mae          Gowers       Chemistry              22         Verizon
     3            Alex           Smith  Gender Studies              53          Amazon

[100]select * from employee where first = Bo or last = Johnson

Table: employee_31 Total Records: 7

Record            last           first             dep          salary            year

     0         Johnson            Jack              HR          150000            2014
     1         Johnson           Jimmy       Chemistry          140000            2018
     2            Yang              Bo              CS          160000            2013
     3         Jackson              Bo       Chemistry          130000            2011
     4         Johnson        Mary Ann            Math          165000            2014
     5         Johnson       Billy Bob         Physics          142000            2014
     6         Johnson           Billy         Phys Ed          102000            2014

[101]select * from employee where year >= 2015 or dep = CS

Table: employee_32 Total Records: 9

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2         Johnson           Jimmy       Chemistry          140000            2018
     3             Yao             Flo              CS          147000            2012
     4            Yang              Bo              CS          160000            2013
     5         Jackson             Flo            Math          165000            2017
     6         Jackson           Billy            Math          170000            2017
     7        Van Gogh         Vincent             Art          240000            2015
     8        Van Gogh         Vincent              CS          245000            2015



//.................
//:OR AND         :
//.................
[102]select * from student where fname = Flo or major = CS and age <= 23

Table: student_41 Total Records: 3

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1             Flo         Jackson            Math              21          Google
     2      Anna Grace         Del Rio              CS              22            USAF

[103]select * from student where lname = Jackson or age < 23 and company > Uber

Table: student_42 Total Records: 3

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1             Flo         Jackson            Math              21          Google
     2      Teresa Mae          Gowers       Chemistry              22         Verizon

[104]select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000

Table: employee_33 Total Records: 5

Record            last           first             dep          salary            year

     0         Jackson             Flo            Math          165000            2017
     1         Jackson           Billy            Math          170000            2017
     2        Van Gogh         Vincent             Art          240000            2015
     3        Van Gogh         Vincent              CS          245000            2015
     4        Van Gogh         Jim Bob         Phys Ed          230000            2010



//.................
//:AND OR AND     :
//.................

[105]select * from student where age <30 and major=CS or major = Physics and company = Amazon

Table: student_43 Total Records: 4

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2            Greg         Pearson         Physics              20          Amazon
     3      Anna Grace         Del Rio              CS              22            USAF

[106]select * from student where age <=40 and company=Uber or major = CS and company = Google

Table: student_44 Total Records: 3

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1      Sammuel L.         Jackson              CS              40            Uber
     2          Calvin             Woo         Physics              22            Uber

[107]select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"

Table: employee_34 Total Records: 3

Record            last           first             dep          salary            year

     0            Yang              Bo              CS          160000            2013
     1        Van Gogh         Vincent             Art          240000            2015
     2        Van Gogh         Vincent              CS          245000            2015



//.................
//:OR AND OR      :
//.................

[108]select * from student where lname = Yang or major = CS and age < 23 or company = Google

Table: student_45 Total Records: 4

Record           fname           lname           major             age         company

     0             Flo             Yao              CS              20          Google
     1              Bo            Yang              CS              28       Microsoft
     2             Flo         Jackson            Math              21          Google
     3      Anna Grace         Del Rio              CS              22            USAF

[109]select * from student where major = Physics or major = Math and company = Google or lname = Jackson

Table: student_46 Total Records: 4

Record           fname           lname           major             age         company

     0      Sammuel L.         Jackson              CS              40            Uber
     1             Flo         Jackson            Math              21          Google
     2            Greg         Pearson         Physics              20          Amazon
     3          Calvin             Woo         Physics              22            Uber

[110]select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 265000

Table: employee_35 Total Records: 8

Record            last           first             dep          salary            year

     0            Blow             Joe              CS          100000            2018
     1            Blow           JoAnn         Physics          200000            2016
     2             Yao             Flo              CS          147000            2012
     3            Yang              Bo              CS          160000            2013
     4         Jackson             Flo            Math          165000            2017
     5         Jackson           Billy            Math          170000            2017
     6        Van Gogh         Vincent             Art          240000            2015
     7        Van Gogh         Vincent              CS          245000            2015













----------------END OF BATCH FILE---------------------
> exit


*/