struct
{
	int i;
	char c;
} s1;

struct sTp
{
	int i;
	char c;
} s2;

struct sTp2
{
	int i;
	char c;
	struct sTp s;
};

struct sTp2 s3;

typedef struct sTp3
{
	int i;
	char c;
} sTp4;

struct sTp3 s4;
sTp4 s5;

int main()
{
	s1.i = s2.c;
	s3.c = s3.s.i;
	s4.c = s5.i;
	return 0;
}
