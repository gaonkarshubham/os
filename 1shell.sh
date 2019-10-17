echo "**********Address Book**********"  					#Title of the assignment
ch=0; 										#Variable for while loop
i=0; 										#Variable for "insert" while loop
while [ $ch -lt 6 ] 								#MENU
do 										#Start while
	echo "1.Create Address Book"						#Display contents with echo command
	echo "2.View Address Book"
	echo "3.Insert a record"
	echo "4.Delete a record"
	echo "5.Modify a record"
	echo "6.Exit"
	echo "Enter your choice"
	read ch 								#Read contents in a variable
	case $ch in								#Using switch case
	1)	
		echo "Enter file name"						#Reading the File Name
		read fname
		touch fname							#Creating an empty file
		echo -e "Roll no.\tName\tBuilding Name\tFlat No.\tArea\tCity\tState\tPincode">$fname	#Writing in file created
		echo "File Created Successfully"
		echo "How many records do you wish to enter?"			#Getting no. of records from user
		read n								#Reading no. of records in a varaible
		while [ $i -ne $n ]						#Starting another while
		do		
			echo "Enter Roll number: "				#Reading the user Data
			read roll
			echo "Enter Name: "
			read name
			echo "Enter Building Name: "
			read bn
			echo "Enter Flat Number: "
			read fn
			echo "Enter Area: "
			read area
			echo "Enter City: "
			read city
			echo "Enter State: "
			read state
			echo "Enter Pincode: "
			read pin
			echo -e "$roll\t$name\t$bn\t$fn\t$area\t$city\t$state\t$pin">>$fname
			echo "Record Inserted Successfully"
			i=`expr $i + 1`							#Incrementing i
		done
		;;									#Case 1 ends
	2)
		cat $fname								#Display contents of the created file
		;;
	3)
		echo "Enter Roll number: "						#Insert a Record in database
		read roll
		echo "Enter Name: "
		read name
		echo "Enter Building Name: "
		read bn
		echo "Enter Flat Number: "
		read fn
		echo "Enter Area: "
		read area
		echo "Enter City: "
		read city
		echo "Enter State: "
		read state
		echo "Enter Pincode: "
		read pin
		
		echo -e "$roll\t$name\t$bn\t$fn\t$area\t$city\t$state\t$pin">>$fname
		echo "Record Inserted Successfully"
		;;
	4)
		echo "Enter roll number of Record to be deleted"	
		read rollno
		if grep -q $rollno "$fname"						#Searching the roll number in file
		then
			echo "Record found."						#If record is found
			grep -w -v $rollno $fname>temp1				 	#Copy all records other than the searched in temp file
			rm $fname							#Remove Orignal File
			mv temp1 $fname							#Rename temp to Orginal filename
			echo "Record deleted successfully"
		else
			echo "Record not found"						#Else Record not found
		fi
		;;
	5)
		echo "Enter the roll no of record to be modified"
		read rollno								#Read the roll no in file
		if grep -q $rollno "$fname"						#If Record is found modify
		then
			echo "Record found, enter the new data: "			
			grep -w -v $rollno $fname>temp1
			rm $fname
			mv temp1 $fname
			echo "Enter Roll number: "
			read roll
			echo "Enter Name: "
			read name
			echo "Enter Building Name: "
			read bn
			echo "Enter Flat Number: "
			read fn
			echo "Enter Area: "
			read area
			echo "Enter City: "
			read city
			echo "Enter State: "
			read state
			echo "Enter Pincode: "
			read pin		
			echo -e "$roll\t$name\t$bn\t$fn\t$area\t$city\t$state\t$pin">>$fname
			echo "Record Inserted Successfully"
		else
			echo "Record not found"						
		fi
		;;
	esac
done



#Output
#[admin@localhost 1]$ ./shell.sh
#**********Address Book**********
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#1
#Enter file name
#class
#File Created Successfully
#How many records do you wish to enter?
#4
#Enter Roll number: 
#1
#Enter Name: 
#shubham gaonkar 
#Enter Building Name: 
#vijaydurga
#Enter Flat Number: 
#412
#Enter Area: 
#40
#Enter City: 
#pune
#Enter State: 
#maharastra
#Enter Pincode: 
#416604
#Record Inserted Successfully
#Enter Roll number: 
#2
#Enter Name: 
#siddhesh gage
#Enter Building Name: 
#lohagad
#Enter Flat Number: 
#412
#Enter Area: 
#42
#Enter City: 
#mumbai
#Enter State: 
#maharastra
#Enter Pincode: 
#412627
#Record Inserted Successfully
#Enter Roll number: 
#3
#Enter Name: 
#shubhangi
#Enter Building Name: 
#narmada
#Enter Flat Number: 
#451
#Enter Area: 
#45
#Enter City: 
#nanded
#Enter State: 
#maharastra
#Enter Pincode: 
#421718
#Record Inserted Successfully
#Enter Roll number: 
#4
#Enter Name: 
#hrushikesh 
#Enter Building Name: 
#kaveri
#Enter Flat Number: 
#421
#Enter Area: 
#64
#Enter City: 
#karnatka
#Enter State: 
#karnatka
#Enter Pincode: 
#417875 
#Record Inserted Successfully
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#2
#Roll no.	Name       	Building Name	Flat No.	Area	City		State		Pincode
#1	shubham gaonkar	vijaydurga		412		40		pune	maharastra	416604
#2	siddhesh gage	           lohagad		412		42		mumbai	maharastra	412627
#3	shubhangi	         narmada		451		45		nanded	maharastra	421718
#4	hrushikesh	            kaveri	         	421		64		karnatka	karnatka		417875
#1.Create Address Book
#2.View Address Book
#33.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#3
#Enter Roll number: 
#5
#Enter Name: 
#yogita wani
#Enter Building Name: 
#kaveri
#Enter Flat Number: 
#213
#Enter Area: 
#46
#Enter City: 
#ahamadnagar
#Enter State: 
#maharastra
#Enter Pincode: 
#412654
#Record Inserted Successfully
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#4
#Enter roll number of Record to be deleted
#4
#Record found.
#Record deleted successfully
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#2
#Roll no.	Name			Building Name	Flat No.	Area	City			State		Pincode
#1		shubham gaonkar	vijaydurga		412		40		pune		maharastra	416604
#2		siddhesh gage	l	ohagad			412		42		mumbai		maharastra	412627
#3		shubhangi		narmada			451		45		nanded		maharastra	421718
#5		yogita wani		kaveri			213		46		ahamadnagar	maharastra	412654
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#5
#Enter the roll no of record to be modified
#3
#Record found, enter the new data: 
#Enter Roll number: 
#3
#Enter Name: 
#shubhangi gulave
#Enter Building Name: 
#narmada
#Enter Flat Number: 
#451
#Enter Area: 
#45
#Enter City: 
#nanded
#Enter State: 
#maharastra
#Enter Pincode: 
#421781
#Record Inserted Successfully
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#2
#Roll no.	Name       	Building Name	Flat No.	Area	City		State		Pincode
#1	shubham gaonkar	vijaydurga		412		40		pune	maharastra	416604
#2	siddhesh gage	           lohagad		412		42		mumbai	maharastra	412627
#3	shubhangi gulave	   narmada		451		45		nanded	maharastra	421718
#4	hrushikesh	            kaveri	         	421		64		karnatka	karnatka		417875
#1.Create Address Book
#2.View Address Book
#3.Insert a record
#4.Delete a record
#5.Modify a record
#6.Exit
#Enter your choice
#6
#[admin@localhost 1]$ 

