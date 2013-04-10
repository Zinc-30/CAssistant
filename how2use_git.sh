1.If you want to use SSH (RSA key) login, get hang of it.

2.Set user name
	$git config --global user.name [your name]
	$git config --global user.email [email]

3.Make working directory
	mkdir and cd into it
	NOTE: if you want to manage a project previously hosted online,
			first use $git clone and then use $git init
		and make an alias of the repo name using:
			$git remote add [alias] [repo destination]
	$git init

4.Create your files
	after creating your own files use $git add 
		to add you files into .git

5.Commit
	$git commit -m [message]
	$git push [alias] [branch_name]
		default branch is "master"
	or simplely use $git push
	$git commit -a #auto commit CLI manager
		so $git commit -a -m [messg] is more convenient
	NOTE:
		eg. you want to add a file to the .git
			$touch [filename]
			$git add [that filename]
		
6.Manage a branch
	create a new branch $git branch [new branch name]	
	show current branch $git branch
	swithch to a branch $git checkout [branch name]
	
7.Merge branches
	#this action will diff anything between certain branches and merge them
	$git checkout [branch where the code will be added to]
	$git merge [branch which will be merged]
