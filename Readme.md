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

# Q2
# all things are same as Question 1 
# but it is assumed that libraries of III-Delhi & AIIMS Delhi are used 
# when book is not found in our library it goes to other 2 libraries
# 6 books 3 from each has all details
# user can search it (same as part 1), get it's location , and then issue it (same as above)
# then execute the following using GitBash

# Question 2
	g++ -c q2.cpp
	g++ -g -o debug2 q2.o
	g++ -O3 -o optimize2 q2.o

	./debug2

# Q3
# all is ame as part 1 , budget is fixed at 1000
# journal array has all journals
# whole journals' list is displayed then user uses S.No. to search from it
# assume journal no. 75-98 are out of budget
# if not subscribed then there is instant subscription and each subscribed journal cost = 10 is deducted from budget , then issued
# for unsubscribed journals , there exist a track of requests made in req[]
# if already subscribed then instantly issued
# then execute the following using GitBash

# Question 3

	g++ -c 3.cpp
	g++ -g -o debug3 3.o
	g++ -O3 -o optimize3 3.o

	./debug3    

# Question 2
	g++ -c 2.cpp
	g++ -g -o debug2 2.o
	g++ -O3 -o optimize2 2.o

	./debug2

# Question 3
	g++ -c 3.cpp
	g++ -g -o debug3 3.o
	g++ -O3 -o optimize3 3.o

	./debug3