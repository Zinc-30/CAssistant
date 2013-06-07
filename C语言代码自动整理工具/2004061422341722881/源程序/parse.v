#############################################################################
#                     U N R E G I S T E R E D   C O P Y
# 
# You are on day 85 of your 30 day trial period.
# 
# This file was produced by an UNREGISTERED COPY of Parser Generator. It is
# for evaluation purposes only. If you continue to use Parser Generator 30
# days after installation then you are required to purchase a license. For
# more information see the online help or go to the Bumble-Bee Software
# homepage at:
# 
# http://www.bumblebeesoftware.com
# 
# This notice must remain present in the file. It cannot be removed.
#############################################################################

#############################################################################
# parse.v
# YACC verbose file generated from parse.y.
# 
# Date: 06/24/03
# Time: 17:07:53
# 
# AYACC Version: 2.05
#############################################################################


##############################################################################
# Rules
##############################################################################

    0  $accept : program $end

    1  program : dec_list

    2  dec_list : dec_list dec
    3           | dec

    4  dec : var_dec
    5      | fun_dec
    6      | fun_def

    7  id : ID

    8  fid :

    9  var_dec : type_spec id_list SEMI

   10  id_list : id_list COMMA var
   11          | var
   12          | id_list COMMA id ASSIGN simple_exp
   13          | id ASSIGN simple_exp

   14  type_spec : INT
   15            | FLOAT
   16            | CHAR
   17            | VOID

   18  fun_def : type_spec id fid LP params RP comp_stmt
   19          | id fid LP params RP comp_stmt

   20  fun_dec : type_spec id fid LP params RP SEMI
   21          | id fid LP params RP SEMI

   22  params : param_list
   23         |

   24  param_list : param_list COMMA param
   25             | param

   26  param : type_spec
   27        | type_spec id
   28        | type_spec id LSP RSP
   29        | type_spec id LSP simple_exp RSP

   30  comp_stmt : LFP local_dec stmt_list RFP

   31  local_dec : local_dec var_dec
   32            |

   33  stmt_list : stmt_list stmt
   34            |

   35  stmt : exp_stmt
   36       | sele_stmt
   37       | iter_stmt
   38       | return_stmt
   39       | comp_stmt
   40       | CONTINUE SEMI
   41       | BREAK SEMI

   42  exp_stmt : exp SEMI
   43           | SEMI

   44  sele_stmt : IF LP exp RP stmt
   45            | IF LP exp RP stmt ELSE stmt

   46  iter_stmt : WHILE LP exp RP stmt

   47  return_stmt : RETURN SEMI
   48              | RETURN exp SEMI

   49  exp : var ASSIGN exp
   50      | simple_exp

   51  var : id
   52      | id LSP simple_exp RSP

   53  simple_exp : simple_exp OR simple_exp
   54             | simple_exp AND simple_exp
   55             | simple_exp LT simple_exp
   56             | simple_exp LE simple_exp
   57             | simple_exp GT simple_exp
   58             | simple_exp GE simple_exp
   59             | simple_exp EQ simple_exp
   60             | simple_exp NEQ simple_exp
   61             | simple_exp PLUS simple_exp
   62             | simple_exp SUB simple_exp
   63             | simple_exp MUT simple_exp
   64             | simple_exp DIV simple_exp
   65             | factor

   66  factor : LP exp RP
   67         | var
   68         | call
   69         | NUM
   70         | FNUM
   71         | SCHAR
   72         | NOT factor

   73  call : var LP args RP

   74  arg_list : arg_list COMMA exp
   75           | exp

   76  args : arg_list
   77       |


##############################################################################
# States
##############################################################################

state 0
	$accept : . program $end

	INT  shift 1
	CHAR  shift 2
	FLOAT  shift 3
	VOID  shift 4
	ID  shift 5

	program  goto 6
	dec_list  goto 7
	dec  goto 8
	var_dec  goto 9
	fun_dec  goto 10
	fun_def  goto 11
	type_spec  goto 12
	id  goto 13


state 1
	type_spec : INT .  (14)

	.  reduce 14


state 2
	type_spec : CHAR .  (16)

	.  reduce 16


state 3
	type_spec : FLOAT .  (15)

	.  reduce 15


state 4
	type_spec : VOID .  (17)

	.  reduce 17


state 5
	id : ID .  (7)

	.  reduce 7


state 6
	$accept : program . $end  (0)

	$end  accept


state 7
	program : dec_list .  (1)
	dec_list : dec_list . dec

	INT  shift 1
	CHAR  shift 2
	FLOAT  shift 3
	VOID  shift 4
	ID  shift 5
	.  reduce 1

	dec  goto 14
	var_dec  goto 9
	fun_dec  goto 10
	fun_def  goto 11
	type_spec  goto 12
	id  goto 13


state 8
	dec_list : dec .  (3)

	.  reduce 3


state 9
	dec : var_dec .  (4)

	.  reduce 4


state 10
	dec : fun_dec .  (5)

	.  reduce 5


state 11
	dec : fun_def .  (6)

	.  reduce 6


state 12
	var_dec : type_spec . id_list SEMI
	fun_def : type_spec . id fid LP params RP comp_stmt
	fun_dec : type_spec . id fid LP params RP SEMI

	ID  shift 5

	var  goto 15
	id_list  goto 16
	id  goto 17


state 13
	fun_def : id . fid LP params RP comp_stmt
	fun_dec : id . fid LP params RP SEMI
	fid : .  (8)

	.  reduce 8

	fid  goto 18


state 14
	dec_list : dec_list dec .  (2)

	.  reduce 2


state 15
	id_list : var .  (11)

	.  reduce 11


state 16
	var_dec : type_spec id_list . SEMI
	id_list : id_list . COMMA var
	id_list : id_list . COMMA id ASSIGN simple_exp

	SEMI  shift 19
	COMMA  shift 20


state 17
	id_list : id . ASSIGN simple_exp
	fun_def : type_spec id . fid LP params RP comp_stmt
	fun_dec : type_spec id . fid LP params RP SEMI
	var : id .  (51)
	var : id . LSP simple_exp RSP
	fid : .  (8)

	ASSIGN  shift 21
	LSP  shift 22
	LP  reduce 8
	.  reduce 51

	fid  goto 23


state 18
	fun_def : id fid . LP params RP comp_stmt
	fun_dec : id fid . LP params RP SEMI

	LP  shift 24


state 19
	var_dec : type_spec id_list SEMI .  (9)

	.  reduce 9


state 20
	id_list : id_list COMMA . var
	id_list : id_list COMMA . id ASSIGN simple_exp

	ID  shift 5

	var  goto 25
	id  goto 26


state 21
	id_list : id ASSIGN . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 33
	factor  goto 34
	call  goto 35
	id  goto 36


state 22
	var : id LSP . simple_exp RSP

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 37
	factor  goto 34
	call  goto 35
	id  goto 36


state 23
	fun_def : type_spec id fid . LP params RP comp_stmt
	fun_dec : type_spec id fid . LP params RP SEMI

	LP  shift 38


state 24
	fun_def : id fid LP . params RP comp_stmt
	fun_dec : id fid LP . params RP SEMI
	params : .  (23)

	INT  shift 1
	CHAR  shift 2
	FLOAT  shift 3
	VOID  shift 4
	.  reduce 23

	params  goto 39
	param_list  goto 40
	param  goto 41
	type_spec  goto 42


state 25
	id_list : id_list COMMA var .  (10)

	.  reduce 10


state 26
	id_list : id_list COMMA id . ASSIGN simple_exp
	var : id .  (51)
	var : id . LSP simple_exp RSP

	ASSIGN  shift 43
	LSP  shift 22
	.  reduce 51


state 27
	factor : NUM .  (69)

	.  reduce 69


state 28
	factor : FNUM .  (70)

	.  reduce 70


state 29
	factor : SCHAR .  (71)

	.  reduce 71


state 30
	factor : NOT . factor

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	factor  goto 44
	call  goto 35
	id  goto 36


state 31
	factor : LP . exp RP

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	exp  goto 45
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 32
	factor : var .  (67)
	call : var . LP args RP

	LP  shift 48
	.  reduce 67


state 33
	id_list : id ASSIGN simple_exp .  (13)
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	AND  shift 59
	OR  shift 60
	.  reduce 13


state 34
	simple_exp : factor .  (65)

	.  reduce 65


state 35
	factor : call .  (68)

	.  reduce 68


state 36
	var : id .  (51)
	var : id . LSP simple_exp RSP

	LSP  shift 22
	.  reduce 51


state 37
	var : id LSP simple_exp . RSP
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	AND  shift 59
	OR  shift 60
	RSP  shift 61


state 38
	fun_def : type_spec id fid LP . params RP comp_stmt
	fun_dec : type_spec id fid LP . params RP SEMI
	params : .  (23)

	INT  shift 1
	CHAR  shift 2
	FLOAT  shift 3
	VOID  shift 4
	.  reduce 23

	params  goto 62
	param_list  goto 40
	param  goto 41
	type_spec  goto 42


state 39
	fun_def : id fid LP params . RP comp_stmt
	fun_dec : id fid LP params . RP SEMI

	RP  shift 63


state 40
	params : param_list .  (22)
	param_list : param_list . COMMA param

	COMMA  shift 64
	.  reduce 22


state 41
	param_list : param .  (25)

	.  reduce 25


state 42
	param : type_spec .  (26)
	param : type_spec . id
	param : type_spec . id LSP RSP
	param : type_spec . id LSP simple_exp RSP

	ID  shift 5
	.  reduce 26

	id  goto 65


state 43
	id_list : id_list COMMA id ASSIGN . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 66
	factor  goto 34
	call  goto 35
	id  goto 36


state 44
	factor : NOT factor .  (72)

	.  reduce 72


state 45
	factor : LP exp . RP

	RP  shift 67


state 46
	exp : var . ASSIGN exp
	factor : var .  (67)
	call : var . LP args RP

	ASSIGN  shift 68
	LP  shift 48
	.  reduce 67


state 47
	exp : simple_exp .  (50)
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	AND  shift 59
	OR  shift 60
	.  reduce 50


state 48
	call : var LP . args RP
	args : .  (77)

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31
	.  reduce 77

	exp  goto 69
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	args  goto 70
	arg_list  goto 71
	id  goto 36


state 49
	simple_exp : simple_exp PLUS . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 72
	factor  goto 34
	call  goto 35
	id  goto 36


state 50
	simple_exp : simple_exp SUB . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 73
	factor  goto 34
	call  goto 35
	id  goto 36


state 51
	simple_exp : simple_exp MUT . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 74
	factor  goto 34
	call  goto 35
	id  goto 36


state 52
	simple_exp : simple_exp DIV . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 75
	factor  goto 34
	call  goto 35
	id  goto 36


state 53
	simple_exp : simple_exp LT . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 76
	factor  goto 34
	call  goto 35
	id  goto 36


state 54
	simple_exp : simple_exp LE . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 77
	factor  goto 34
	call  goto 35
	id  goto 36


state 55
	simple_exp : simple_exp GT . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 78
	factor  goto 34
	call  goto 35
	id  goto 36


state 56
	simple_exp : simple_exp GE . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 79
	factor  goto 34
	call  goto 35
	id  goto 36


state 57
	simple_exp : simple_exp EQ . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 80
	factor  goto 34
	call  goto 35
	id  goto 36


state 58
	simple_exp : simple_exp NEQ . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 81
	factor  goto 34
	call  goto 35
	id  goto 36


state 59
	simple_exp : simple_exp AND . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 82
	factor  goto 34
	call  goto 35
	id  goto 36


state 60
	simple_exp : simple_exp OR . simple_exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	var  goto 32
	simple_exp  goto 83
	factor  goto 34
	call  goto 35
	id  goto 36


state 61
	var : id LSP simple_exp RSP .  (52)

	.  reduce 52


state 62
	fun_def : type_spec id fid LP params . RP comp_stmt
	fun_dec : type_spec id fid LP params . RP SEMI

	RP  shift 84


state 63
	fun_def : id fid LP params RP . comp_stmt
	fun_dec : id fid LP params RP . SEMI

	SEMI  shift 85
	LFP  shift 86

	comp_stmt  goto 87


state 64
	param_list : param_list COMMA . param

	INT  shift 1
	CHAR  shift 2
	FLOAT  shift 3
	VOID  shift 4

	param  goto 88
	type_spec  goto 42


state 65
	param : type_spec id .  (27)
	param : type_spec id . LSP RSP
	param : type_spec id . LSP simple_exp RSP

	LSP  shift 89
	.  reduce 27


state 66
	id_list : id_list COMMA id ASSIGN simple_exp .  (12)
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	AND  shift 59
	OR  shift 60
	.  reduce 12


state 67
	factor : LP exp RP .  (66)

	.  reduce 66


state 68
	exp : var ASSIGN . exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	exp  goto 90
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 69
	arg_list : exp .  (75)

	.  reduce 75


state 70
	call : var LP args . RP

	RP  shift 91


state 71
	arg_list : arg_list . COMMA exp
	args : arg_list .  (76)

	COMMA  shift 92
	.  reduce 76


state 72
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp PLUS simple_exp .  (61)
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	MUT  shift 51
	DIV  shift 52
	.  reduce 61


state 73
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp SUB simple_exp .  (62)
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	MUT  shift 51
	DIV  shift 52
	.  reduce 62


state 74
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp MUT simple_exp .  (63)
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	.  reduce 63


state 75
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp DIV simple_exp .  (64)
	simple_exp : simple_exp . DIV simple_exp

	.  reduce 64


state 76
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp LT simple_exp .  (55)
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	.  reduce 55


state 77
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp LE simple_exp .  (56)
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	.  reduce 56


state 78
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp GT simple_exp .  (57)
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	.  reduce 57


state 79
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp GE simple_exp .  (58)
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	.  reduce 58


state 80
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp EQ simple_exp .  (59)
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	.  reduce 59


state 81
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp NEQ simple_exp .  (60)
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	.  reduce 60


state 82
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp AND simple_exp .  (54)
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	.  reduce 54


state 83
	simple_exp : simple_exp OR simple_exp .  (53)
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	AND  shift 59
	.  reduce 53


state 84
	fun_def : type_spec id fid LP params RP . comp_stmt
	fun_dec : type_spec id fid LP params RP . SEMI

	SEMI  shift 93
	LFP  shift 86

	comp_stmt  goto 94


state 85
	fun_dec : id fid LP params RP SEMI .  (21)

	.  reduce 21


state 86
	comp_stmt : LFP . local_dec stmt_list RFP
	local_dec : .  (32)

	.  reduce 32

	local_dec  goto 95


state 87
	fun_def : id fid LP params RP comp_stmt .  (19)

	.  reduce 19


state 88
	param_list : param_list COMMA param .  (24)

	.  reduce 24


state 89
	param : type_spec id LSP . RSP
	param : type_spec id LSP . simple_exp RSP

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31
	RSP  shift 96

	var  goto 32
	simple_exp  goto 97
	factor  goto 34
	call  goto 35
	id  goto 36


state 90
	exp : var ASSIGN exp .  (49)

	.  reduce 49


state 91
	call : var LP args RP .  (73)

	.  reduce 73


state 92
	arg_list : arg_list COMMA . exp

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	exp  goto 98
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 93
	fun_dec : type_spec id fid LP params RP SEMI .  (20)

	.  reduce 20


state 94
	fun_def : type_spec id fid LP params RP comp_stmt .  (18)

	.  reduce 18


state 95
	comp_stmt : LFP local_dec . stmt_list RFP
	local_dec : local_dec . var_dec
	stmt_list : .  (34)

	INT  shift 1
	CHAR  shift 2
	FLOAT  shift 3
	VOID  shift 4
	.  reduce 34

	var_dec  goto 99
	stmt_list  goto 100
	type_spec  goto 101


state 96
	param : type_spec id LSP RSP .  (28)

	.  reduce 28


state 97
	param : type_spec id LSP simple_exp . RSP
	simple_exp : simple_exp . OR simple_exp
	simple_exp : simple_exp . AND simple_exp
	simple_exp : simple_exp . LT simple_exp
	simple_exp : simple_exp . LE simple_exp
	simple_exp : simple_exp . GT simple_exp
	simple_exp : simple_exp . GE simple_exp
	simple_exp : simple_exp . EQ simple_exp
	simple_exp : simple_exp . NEQ simple_exp
	simple_exp : simple_exp . PLUS simple_exp
	simple_exp : simple_exp . SUB simple_exp
	simple_exp : simple_exp . MUT simple_exp
	simple_exp : simple_exp . DIV simple_exp

	PLUS  shift 49
	SUB  shift 50
	MUT  shift 51
	DIV  shift 52
	LT  shift 53
	LE  shift 54
	GT  shift 55
	GE  shift 56
	EQ  shift 57
	NEQ  shift 58
	AND  shift 59
	OR  shift 60
	RSP  shift 102


state 98
	arg_list : arg_list COMMA exp .  (74)

	.  reduce 74


state 99
	local_dec : local_dec var_dec .  (31)

	.  reduce 31


state 100
	comp_stmt : LFP local_dec stmt_list . RFP
	stmt_list : stmt_list . stmt

	IF  shift 103
	WHILE  shift 104
	RETURN  shift 105
	BREAK  shift 106
	CONTINUE  shift 107
	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	SEMI  shift 108
	LP  shift 31
	LFP  shift 86
	RFP  shift 109

	comp_stmt  goto 110
	stmt  goto 111
	exp_stmt  goto 112
	sele_stmt  goto 113
	iter_stmt  goto 114
	return_stmt  goto 115
	exp  goto 116
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 101
	var_dec : type_spec . id_list SEMI

	ID  shift 5

	var  goto 15
	id_list  goto 16
	id  goto 117


state 102
	param : type_spec id LSP simple_exp RSP .  (29)

	.  reduce 29


state 103
	sele_stmt : IF . LP exp RP stmt
	sele_stmt : IF . LP exp RP stmt ELSE stmt

	LP  shift 118


state 104
	iter_stmt : WHILE . LP exp RP stmt

	LP  shift 119


state 105
	return_stmt : RETURN . SEMI
	return_stmt : RETURN . exp SEMI

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	SEMI  shift 120
	LP  shift 31

	exp  goto 121
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 106
	stmt : BREAK . SEMI

	SEMI  shift 122


state 107
	stmt : CONTINUE . SEMI

	SEMI  shift 123


state 108
	exp_stmt : SEMI .  (43)

	.  reduce 43


state 109
	comp_stmt : LFP local_dec stmt_list RFP .  (30)

	.  reduce 30


state 110
	stmt : comp_stmt .  (39)

	.  reduce 39


state 111
	stmt_list : stmt_list stmt .  (33)

	.  reduce 33


state 112
	stmt : exp_stmt .  (35)

	.  reduce 35


state 113
	stmt : sele_stmt .  (36)

	.  reduce 36


state 114
	stmt : iter_stmt .  (37)

	.  reduce 37


state 115
	stmt : return_stmt .  (38)

	.  reduce 38


state 116
	exp_stmt : exp . SEMI

	SEMI  shift 124


state 117
	id_list : id . ASSIGN simple_exp
	var : id .  (51)
	var : id . LSP simple_exp RSP

	ASSIGN  shift 21
	LSP  shift 22
	.  reduce 51


state 118
	sele_stmt : IF LP . exp RP stmt
	sele_stmt : IF LP . exp RP stmt ELSE stmt

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	exp  goto 125
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 119
	iter_stmt : WHILE LP . exp RP stmt

	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	LP  shift 31

	exp  goto 126
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 120
	return_stmt : RETURN SEMI .  (47)

	.  reduce 47


state 121
	return_stmt : RETURN exp . SEMI

	SEMI  shift 127


state 122
	stmt : BREAK SEMI .  (41)

	.  reduce 41


state 123
	stmt : CONTINUE SEMI .  (40)

	.  reduce 40


state 124
	exp_stmt : exp SEMI .  (42)

	.  reduce 42


state 125
	sele_stmt : IF LP exp . RP stmt
	sele_stmt : IF LP exp . RP stmt ELSE stmt

	RP  shift 128


state 126
	iter_stmt : WHILE LP exp . RP stmt

	RP  shift 129


state 127
	return_stmt : RETURN exp SEMI .  (48)

	.  reduce 48


state 128
	sele_stmt : IF LP exp RP . stmt
	sele_stmt : IF LP exp RP . stmt ELSE stmt

	IF  shift 103
	WHILE  shift 104
	RETURN  shift 105
	BREAK  shift 106
	CONTINUE  shift 107
	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	SEMI  shift 108
	LP  shift 31
	LFP  shift 86

	comp_stmt  goto 110
	stmt  goto 130
	exp_stmt  goto 112
	sele_stmt  goto 113
	iter_stmt  goto 114
	return_stmt  goto 115
	exp  goto 116
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 129
	iter_stmt : WHILE LP exp RP . stmt

	IF  shift 103
	WHILE  shift 104
	RETURN  shift 105
	BREAK  shift 106
	CONTINUE  shift 107
	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	SEMI  shift 108
	LP  shift 31
	LFP  shift 86

	comp_stmt  goto 110
	stmt  goto 131
	exp_stmt  goto 112
	sele_stmt  goto 113
	iter_stmt  goto 114
	return_stmt  goto 115
	exp  goto 116
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 130
	sele_stmt : IF LP exp RP stmt .  (44)
	sele_stmt : IF LP exp RP stmt . ELSE stmt

	ELSE  shift 132
	.  reduce 44


state 131
	iter_stmt : WHILE LP exp RP stmt .  (46)

	.  reduce 46


state 132
	sele_stmt : IF LP exp RP stmt ELSE . stmt

	IF  shift 103
	WHILE  shift 104
	RETURN  shift 105
	BREAK  shift 106
	CONTINUE  shift 107
	ID  shift 5
	NUM  shift 27
	FNUM  shift 28
	SCHAR  shift 29
	NOT  shift 30
	SEMI  shift 108
	LP  shift 31
	LFP  shift 86

	comp_stmt  goto 110
	stmt  goto 133
	exp_stmt  goto 112
	sele_stmt  goto 113
	iter_stmt  goto 114
	return_stmt  goto 115
	exp  goto 116
	var  goto 46
	simple_exp  goto 47
	factor  goto 34
	call  goto 35
	id  goto 36


state 133
	sele_stmt : IF LP exp RP stmt ELSE stmt .  (45)

	.  reduce 45


##############################################################################
# Summary
##############################################################################

38 token(s), 29 nonterminal(s)
78 grammar rule(s), 134 state(s)


##############################################################################
# End of File
##############################################################################
