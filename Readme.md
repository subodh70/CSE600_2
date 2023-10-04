# Q1
# 1st read books & magzines files & store in arrays like title , author , isbn , pub(magzines) , cnt
# user 1st has to register then only items are issued , there exists a record of users who are registered
# there is a combined search + issue function , it searches items by author / ISBN / title using substring search in title array
# if string is found , it displays location (assuming books are in shelevs 1-4 {25 unique books o=in each shelf & 5-8 have magzines})
# it stores the index in ind_store[] where substring is(are found) , then user can press s.no. which will map to title[]
# then checking happens whether user registered or not 
# faculties have ids >= 6000 & students have >= 2000
# issueing is done and corresponding count is decreased by 1
# time of issue & record of issue(both for magazines & books) is kept
# issue functions work same as serach functions , but ids are checked in main() only then search + issue is same as above
# purchase is done again by search functions , then #Copies are asked , according to #Copies count of that book is increased
# then execute the following using GitBash

test : 
# Question 1
	g++ -c q1.cpp
	g++ -g -o debug1 q1.o
	g++ -O3 -o optimize1 q1.o

	./debug1
