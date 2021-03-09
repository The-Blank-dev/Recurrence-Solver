/************
Ashwamegh Rathore
19CS30009
coding test 2
*************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node
{
    int a,b,c,d;
}splnum;

void prnspl ( splnum u );
int val(int x)
{
    if(x!=0)
        return 1;
    else 
        return 0;
}
int is_square(int x)
{
    if(x<0)
        x=x*-1;
    if(sqrt(x)==(int)sqrt(x))
        return 1;
    else
        return 0;
}
int gcd_spl(int d,int c)
{
    if(d<0)
        d*=-1;
    if(c<0)
        c*=-1;
    int i,h=1;
    for(i=1;i<=d&&i<=c*c;i++)
    {
        if(d%(i*i)==0 && (c*c)%(i*i)==0)
            h=i;
    }
    return(h);
}
int gcd(int n1,int n2)
{
    if(n1<0)
        n1*=-1;
    if(n2<0)
        n2*=-1;
    while(n1!=n2)
    {
        if(n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
    return n1;
}
void transform(splnum *u)
{
    int b1=1,i,d1;
    d1=u->d;
    if(d1<0)
        d1*=-1;
    if(is_square(u->d))
    {
        u->a+=sqrt(u->d);
        u->d=0;
    }
    for(i=1;i<=d1;i++)
    {
        if(d1%(i*i)==0)
        {
            b1=i;
        }
    }
    u->b=b1*u->b;
    u->d=u->d/(b1*b1);

}

void reduce(splnum *u)
{
    int hcf,hcf_spl;
    int a,b,c,d;
    a=u->a >0?u->a:-1*u->a;
    b=u->b >0?u->b:-1*u->b;
    c=u->c >0?u->c:-1*u->c;
    d=u->d >0?u->d:-1*u->d;

    hcf_spl=gcd_spl((b)*(b)*(d),c);
    if(d!=0 && a!=0)
        hcf=gcd(gcd(a,c),hcf_spl);
    else if(d==0 && a!=0)
        hcf=gcd(a,c);
    else
        hcf=hcf_spl;
    // printf("%d\n",hcf);
    u->a=u->a/hcf;
    u->c=u->c/hcf;
    u->d=u->d/(hcf*hcf);
}
splnum addspl ( splnum u, splnum v )
{
    if(u.c==0||v.c==0)
    {
        printf("div by 0 not possible\n");
        exit(-1);
    }
    else
    {
    transform(&u);
    transform(&v);
    prnspl(u);
    printf("\n");
    prnspl(v);
    printf("\n");
    if(u.d!=v.d && (u.d)*(v.d)!=0){
        printf("cannot be added\n");
        exit(-1);
    }
    else
    {
        
        splnum temp;
        temp.a=u.a*v.c+v.a*u.c;
        temp.b=u.b*v.c*val(u.d)+v.b*u.c*(val(v.d));
        temp.c=u.c*v.c;
        if(u.d==v.d)
            temp.d=temp.b*temp.b*u.d;
        else 
            temp.d=temp.b*temp.b*(u.d+v.d);
        if(temp.b<0)
            temp.b=-1;
        else
            temp.b=1;
        reduce(&temp);
        return(temp);
    }
    }
}
splnum subspl ( splnum u, splnum v )
{
    if(u.c==0||v.c==0)
    {
        printf("div by 0 not possible\n");
        exit(-1);
    }
    else{
    transform(&u);
    transform(&v);
    //printf("test\n");
    if(u.d!=v.d && (u.d)*(v.d)!=0){
        printf("cannot be substracted\n");
        exit(-1);
    }
    else
    {
        
        splnum temp;
        temp.a=u.a*v.c-v.a*u.c;
        temp.b=u.b*v.c*val(u.d)-v.b*u.c*(val(v.d));
        temp.c=u.c*v.c;
        if(u.d==v.d)
            temp.d=temp.b*temp.b*u.d;
        else 
            temp.d=temp.b*temp.b*(u.d+v.d);
        if(temp.b<0)
            temp.b=-1;
        else
            temp.b=1;
        //prnspl(temp);
        //printf("\n");
        //printf("test\n");
        reduce(&temp);
        //printf("test\n");
        return(temp);
    }
    }
}
splnum mulspl ( splnum u, splnum v )
{
    if(u.c==0||v.c==0)
    {
        printf("div by 0 not possible\n");
        exit(-1);
    }
    else
    {
    splnum temp;
    transform(&u);
    transform(&v);
    if(u.d!=v.d && (u.d)*(v.d)!=0)
    {
        printf("cannot be multiplied\n");
        exit(-1);
    }
    else
    {
        temp.c=(u.c)*(v.c);
        
        temp.b=(u.a)*(v.b)*val(v.d)+(u.b)*(v.a)*val(u.d);
        if(u.d==0){
            temp.d=u.a*u.a*v.b*v.b*v.d;
            temp.a=(u.a)*(v.a);
        }
        else if(v.d==0){
            temp.d=v.a*v.a*u.b*u.b*u.d;
            temp.a=(u.a)*(v.a);
        }
        else{
            temp.d=(temp.b)*(temp.b)*(u.d);
            temp.a=(u.a)*(v.a)+(u.b)*(v.b)*(u.d);
        }
        if(temp.b<0)
            temp.b=-1;
        else
            temp.b=1;
        reduce(&temp);
        return(temp);
    }
    }
}
splnum invspl ( splnum u )
{
    splnum temp;
    transform(&u);
    if(u.a==0&&u.d==0)
    {
        printf("cannot be inverted\n");
        exit(-1);
    }
    else if(u.a==0)
    {
        temp.a=0;
        temp.b=u.b>0?1:-1;
        temp.d=u.d*u.c*u.c;
        temp.c=u.b*u.d;
        reduce(&temp);
        return(temp);
    }
    else if(u.d==0)
    {
        temp.b=u.b>0?1:-1;
        temp.d=0;
        temp.c=u.a;
        temp.a=u.c;
        reduce(&temp);
        return(temp);
    }
    else
    {
        temp.a=u.a*u.c;
        temp.d=u.c*u.c*u.d*u.b*u.b;
        temp.b=u.b>0?-1:1;
        temp.c=u.a*u.a-u.d*u.b*u.b;
        reduce(&temp);
        return(temp);
    }
}
splnum divspl ( splnum u, splnum v )
{
    splnum temp=invspl(v);
    temp=mulspl(u,temp);
    return temp;
}
void prnspl ( splnum u )
{
	if(u.c<0)
	{
		u.a*=-1;
		u.b*=-1;
		u.c*=-1;
	}
    if(u.d==0)
    {
        if(u.c==1)
            printf("%d",u.a);
        else if(u.c==-1)
            printf("%d",-1*u.a);
        else
            printf("%d / %d",u.a,u.c);
    }
    else
    {
        if(u.b>0)
        {
            if(u.c==1)
                printf("%d + sqrt(%d)",u.a,u.d);
            else if(u.c==-1)
                printf("%d - sqrt(%d)",-1*u.a,u.d);
            else
                printf("(%d + sqrt(%d)) / %d",u.a,u.d,u.c);
        }
        else
        {
            if(u.c==1)
                printf("%d - sqrt(%d)",u.a,u.d);
            else if(u.c==-1)
                printf("%d + sqrt(%d)",-1*u.a,u.d);
            else
                printf("(%d - sqrt(%d)) / %d",u.a,u.d,u.c);
        }
    }
}
void findroots ( int r, int s, splnum roots[2] )
{
    roots[0].a=r;
    roots[1].a=r;
    roots[0].b=1;
    roots[1].b=-1;
    roots[0].c=2;
    roots[1].c=2;
    roots[0].d=r*r+4*s;
    roots[1].d=r*r+4*s;
    if(is_square(roots[0].d))
    {
        roots[0].a=r+sqrt(roots[0].d);
        roots[1].a=r-sqrt(roots[0].d);
        roots[0].d=0;
        roots[1].d=0;
    }
    reduce(roots+0);
    reduce(roots+1);
}
int is_one(splnum x)
{
	if(x.a==1 && x.d==0 &&x.c==1)
		return 1;
	else
		return 0;
}

void solvehomogeneous_soln( splnum root[2],int r,int s, splnum A0, splnum A1 )
{
	splnum I;
	I.a=-1;
	I.d=0;
	I.b=1;
	I.c=1;

	splnum c1,c2;
	c1=c2=I;
	if(r*r+4*s!=0)
	{
		c1 = divspl(subspl(A1,mulspl(A0,root[1])),subspl(root[0],root[1]));
        c2=subspl(A0,c1);
        /*
        c2 = divspl(subspl(A1,mulspl(A0,root[0])),subspl(root[1],root[0]));
		splnum temp;
        temp.a=2*c2.a;
        temp.b=1;
        temp.c=c2.c;
        temp.d=0;
        c2=subspl()
        */
        printf("[");
		prnspl(c1);
		printf("] [");
		prnspl(root[0]);
		printf("]^n + ");
		printf("[");
		prnspl(c2);
		printf("] [");
		prnspl(root[1]);
		printf("]^n \n");
	}
	else
	{
		c1=A0;
		c2=subspl(divspl(A1,root[0]),A0);
		printf("[");
		printf("(");
		prnspl(c2);
		printf(")n + (");
		prnspl(c1);
		printf(")] [");
		prnspl(root[0]);
		printf("]^n \n");
	}
}
void solvenonhomogeneous ( int r, int s, int t, int a0, int a1 )
{
    splnum A0,A1;
	splnum root[2];
	findroots(r,s,root);
	printf("+++ Solving the nonhomogeneous recurrence\n");
	printf("    Characteristic equation: x^2+ (%d)x+ (%d) = 0\n",-1*r,-1*s );
	printf("    Root 1 = ");
	prnspl(root[0]);
	printf("\n    Root 2 = ");
	prnspl(root[1]);
	printf("\n    Particular solution : ");
	splnum temp;
    A0.a=a0;
    A0.d=0;
    A0.b=1;
    A0.c=1;

    A1.a=a1;
    A1.d=0;
    A1.b=1;
    A1.c=1;
	if(is_one(root[0]) && is_one(root[1]))
	{
		temp.a=t;
		temp.c=2;
		temp.d=0;
		temp.b=0;
		printf("[");
		prnspl(temp);
		printf("] n^2");
		printf("\n    Homogeneous solution :\n    ");
		solvehomogeneous_soln(root,r,s,A0,subspl(A1,temp));
	}
	else if(is_one(root[0]) || is_one(root[1]))
	{
		temp.a=t;
		temp.c=r+2*s;
		temp.d=0;
		temp.b=0;
		printf("[");
		prnspl(temp);
		printf("] n");
		printf("\n    Homogeneous solution :\n    ");
		solvehomogeneous_soln(root,r,s,A0,subspl(A1,temp));
	}
	else
	{
		temp.a=t;
		temp.c=1-r-s;
		temp.d=0;
		temp.b=0;
		prnspl(temp);
		printf("\n    Homogeneous solution :\n    ");
		solvehomogeneous_soln(root,r,s,subspl(A0,temp),subspl(A1,temp));
	}
	
}
void solvehomogeneous ( int r, int s, int a0, int a1 )
{
    splnum A0,A1;
    A0.a=a0;
    A0.d=0;
    A0.b=1;
    A0.c=1;

    A1.a=a1;
    A1.d=0;
    A1.b=1;
    A1.c=1;
	splnum root[2];
	findroots(r,s,root);
	printf("+++ Solving the homogeneous recurrence\n");
	printf("    Characteristic equation: x^2+ (%d)x+ (%d) = 0\n",-1*r,-1*s );
	printf("    Root 1 = ");
	prnspl(root[0]);
	printf("\n    Root 2 = ");
	prnspl(root[1]);
	printf("\n    Homogeneous solution :\n    ");
	solvehomogeneous_soln(root,r,s,A0,A1);
}
int main()
{
	int r,s,t,a0,a1;
	printf("r=");
	scanf(" %d",&r);
	printf("s=");
	scanf(" %d",&s);
	printf("t=");
	scanf(" %d",&t);
	printf("a0=");
	scanf(" %d",&a0);
	printf("a1=");
	scanf(" %d",&a1);
	
	solvehomogeneous(r,s,a0,a1);
	solvenonhomogeneous(r,s,t,a0,a1);
	return 0;
}