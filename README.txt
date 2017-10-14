************************************************************************************************************************************************************************************************************************************************************
                                                     	   ||  PROJECT TITLE : Criminals Database   ||
*************************************************************************************************************************************************************************************************************************************************************
/*All assign files are the functions created to be used in the main program p09 main.*/
<< 1 >>Introduction and Overview:
---------------------------------------------------------
This project helps to perform a few specific tasks related to maintaining a Criminals Database. This database will have the details of persons with criminal records (person ID, name, offense,
region, prison name, arrest date, release date(if applicable)). Person ID is used as primary key. There are two tables, the main one and an archive, whose details are maintained and updated.
---------------------------------------------------------
<< 2 >>Login Procedure in Database or criminal Record:
**
To login into the Database user should have a valid user-id i.e. in the format of 'user@iiits.in' and also user should have the correct password.
Username : user@iiits.in format.
    ..here user should be initials of iiits mail ID.
Password : iiits
Log of every user who logs in successfully will be saved in a text file storing user-id, date and time.
---------------------------------------------------------
<< 3 >>Subtasks:

    (( i )) Creating a new record : Records are maintained in a txt file and managed by linked list.
            ..User will be prompted for info on the prisoner
            ..PID : Each prisoner will have an unique PID(max 7 digits).
            ..NAME : Name of prisoner.
            ..OFFENCE : If a person commits multiple offence it can be inserted comma separated.
            ..REGION : Region where the crime was committed.
            ..PRISON NAME:  Name of the prison where prisoner is kept.
            ..ARREST DATE : Date of arrest should be less than release date obviously otherwise user will be reprompted for correct info.
            ..RELEASE DATE : Expected release date should be inserted .

    (( ii )) Archive Database:
            ..if any prisoner released after 20 years gap then that record will be transferred into an Archive list and will be maintained in 		separate text file.

    (( iii )) searching : user can search for multiple fields .
            ..NAME : If a name is given the record will be extracted and printed also if some prefix is matched the possible names or records 		will be shown.
            ..PID : If a PID is given the record will be extracted and printed.
            ..REGION : If a REGION is given the record will be extracted and printed.
            ..PRISON NAME : Prison name will searched recursively and printed.
            ..ARREST and RELEASE DATE : A person whose A DATE and R DATE matches will be extracted and printed.

    (( iv )) Modify Database : Valid user can change a specific field according to his or her flexibility.
            ..All fields in the database record can be modified except 'Realease info'.
            ..The user first needs to give a valid PID of the prisoner whose detail has to be modified.

            ..If the PID given is valid, then the user has following options to modify:-
            
            ..PID: In order to modify current PID, the user is prompted a new PID. Now the new entered PID is passed to a function which 		checks whether the given PID is 'unused' or 'already used/same' PID. If the given PID is unique then previous PID is modified 		otherwise user is again prompted to enter new PID(max 3 chances).
            ..NAME : In order to modify current Prisoner name, the user is prompted a new name which is overwritten. Then the modified 		record is displayed.
            ..REGION : In order to modify current region, the user is prompted a new region which again is overwritten and modified record 		is displayed.
            ..PRISON NAME : In order to modify current prison name, the user is prompted a new prison name.
            ..ARREST DATE : In order to modify current Arrest Date, the user is prompted a new Arrest Date(dd/mm/yyyy format).Then this 		date is passed to another function which checks whether the date entered is a valid date or not. If valid changes are made else 		user is again asked for a valid date.
            ..RELEASE DATE: Changes in Release Date is not allowed.

    (( V ))  Release : The date of release will be added into the database
            ..The details of criminals released 20 years or earlier are deleted from the main table and added to a separate table called 		Archive.
