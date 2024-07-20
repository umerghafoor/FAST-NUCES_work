#include<iostream>
#include<iomanip>
#include<windows.h>

    double adjm2[2][2],adjm[3][3],invr[3][3],invr2[2][2];
    int odr;
    double mat2[2][2];
    double mat[3][3];
/**
 * The function displays a 2D array of doubles with a specified precision and formatting.
 * 
 * @param odr odr is an integer parameter that specifies the order of the matrix. It can have a value
 * of either 2 or 3, depending on whether the matrix is a 2x2 or a 3x3 matrix.
 * @param dmat dmat is a 2D array of size 3x3 containing double precision floating point values.
 * @param dmat2 dmat2 is a 2-dimensional array of type double with dimensions 2x2. It is used as a
 * parameter in the function show() to display the values stored in the array.
 */
void show(int odr,double dmat[3][3],double dmat2[2][2])
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,10);
    if(odr==3)
    {
    for(int i=0; i<odr;i++)
            {
                for(int j=0; j<odr;j++)
                {
                    std::cout<<std::setw(6)<<std::setprecision(2)<<dmat[i][j];
                }
                std::cout<<std::endl;
            }
    }
    else if(odr==2)
    {
    for(int i=0; i<odr;i++)
            {
                for(int j=0; j<odr;j++)
                {
                    std::cout<<std::setw(6)<<std::setprecision(3)<<dmat2[i][j];
                }
                std::cout<<std::endl;
            }
    }
    SetConsoleTextAttribute(h,15);
}

/**
 * The function checks if a given matrix is symmetric or not.
 * 
 * @param odr The order of the matrix (either 2 or 3)
 * @param mat A 3x3 matrix of type double.
 * @param mat2 mat2 is a 2x2 matrix of type double.
 */
void sym(int odr,double mat[3][3],double mat2[2][2])
{
bool x=1;
    if(odr==3)
    {
    for(int i=0; i<odr;i++)
            {
                for(int j=0; j<odr;j++)
                {
                    if(mat[i][j]!=mat[j][i]){x=0;}
                }
            }
    }
    if(odr==2)
    {
    for(int i=0; i<odr;i++)
            {
                for(int j=0; j<odr;j++)
                {
                    if(mat2[i][j]!=mat2[j][i]){x=0;}
                }
            }
    }

    if(x){std::cout<<" Matrix is symytrical"<<std::endl;}
    else {std::cout<<" Matrix is not symytrical"<<std::endl;}
}

/**
 * The function checks if a given matrix is an identity matrix or not.
 * 
 * @param odr The order of the matrix, which can be either 2 or 3.
 * @param mat The parameter "mat" is a 3x3 matrix of type double.
 * @param mat2 mat2 is a 2x2 matrix of type double.
 */
void id(int odr,double mat[3][3],double mat2[2][2])
{
bool x=1;
if(odr==3)
{
    for(int i=0; i<odr;i++)
            {
                    if(mat[i][i]!=1){x=0;}
                    for(int j=0; j<odr;j++)
                {
                    if(i!=j){if(mat[i][j]!=0){x=0;}}
                }
            }
}
if(odr==2)
{
    for(int i=0; i<odr;i++)
            {
                    if(mat2[i][i]!=1){x=0;}
                    for(int j=0; j<odr;j++)
                {
                    if(i!=j){if(mat2[i][j]!=0){x=0;}}
                }
            }
}

    if(x){std::cout<<" Matrix is Identity matrix"<<std::endl;}
    else {std::cout<<" Matrix is not a identity matrix"<<std::endl;}
}

/**
 * The function takes in two matrices and solves for the variables using matrix inversion.
 * 
 * @param odr The parameter "odr" is an integer variable that determines the order of the matrix. It
 * can have a value of either 2 or 3, indicating whether the matrix is a 2x2 or a 3x3 matrix.
 * @param mat A 3x3 matrix of type double.
 * @param mat2 The parameter "mat2" is a 2x2 matrix of type double.
 */
void solve(int odr,double mat[3][3],double mat2[2][2])
{
    double cff[3];
    double a,b,c;
    if(odr==3)
        {
            std::cout<<"Enter the mat 1 :";std::cin>>cff[0];
            std::cout<<"Enter the mat 2 :";std::cin>>cff[1];
            std::cout<<"Enter the mat 3 :";std::cin>>cff[2];
            a=(invr[0][0]*cff[0])+(invr[0][1]*cff[1])+(invr[0][2]*cff[2]);
            b=(invr[1][0]*cff[0])+(invr[1][1]*cff[1])+(invr[1][2]*cff[2]);
            c=(invr[2][0]*cff[0])+(invr[2][1]*cff[1])+(invr[2][2]*cff[2]);
            std::cout<<"X = "<<a<<std::endl<<"Y = "<<b<<std::endl<<"Z= "<<c<<std::endl;
        }
    if(odr==2)
        {
            std::cout<<"Enter the mat 1 :";std::cin>>cff[0];
            std::cout<<"Enter the mat 2 :";std::cin>>cff[1];
            a=(invr2[0][0]*cff[0])+(invr2[0][1]*cff[1]);
            b=(invr2[1][0]*cff[0])+(invr2[1][1]*cff[1]);
            std::cout<<"X = "<<a<<std::endl<<"Y = "<<b<<std::endl;
        }
}
/**
 * The function calculates the determinant of a 2x2 or 3x3 matrix.
 * 
 * @param odr The order of the matrix (either 2 or 3)
 * @param mat A 3x3 matrix of doubles
 * @param mat2 mat2 is a 2x2 matrix of type double. It is used to calculate the determinant of a 2x2
 * matrix.
 * 
 * @return the determinant of a 2x2 or 3x3 matrix, depending on the value of the parameter "odr".
 */
double det(int odr,double mat[3][3],double mat2[2][2])
{
    int det;
    int a1,a2,a3;
    if(odr==2)
    {
        det=(mat2[0][0]*mat2[1][1])-(mat2[0][1]*mat2[1][0]);
    }
    if(odr==3)
    {
        det=mat[0][0]*((mat[1][1]*mat[2][2])-(mat[1][2]*mat[2][1]))
        -mat[1][0]*((mat[0][1]*mat[2][2])-(mat[0][2]*mat[2][1]))
        +mat[2][0]*((mat[0][1]*mat[1][2])-(mat[0][2]*mat[1][1]));
    }
    return det;
}
/**
 * The function calculates the adjoint matrix of a given matrix of order 2 or 3.
 * 
 * @param odr odr is an integer parameter that specifies the order of the matrix. It can have a value
 * of either 2 or 3.
 * @param mat The parameter "mat" is a 3x3 matrix of type double.
 * @param mat2 mat2 is a 2x2 matrix of type double. It is used as an input parameter in the function
 * adj() to calculate its adjoint matrix adjm2. The adjoint matrix of a 2x2 matrix is obtained by
 * swapping the positions of the elements in the main diagonal,
 */
void adj(int odr,double mat[3][3],double mat2[2][2])
{
    if(odr==3)
    {
                adjm[0][0]=(mat[1][1]*mat[2][2])-(mat[2][1]*mat[1][2]);
                adjm[1][0]=-((mat[1][0]*mat[2][2])-(mat[2][0]*mat[1][2]));
                adjm[2][0]=(mat[1][0]*mat[2][1])-(mat[2][0]*mat[1][1]);
                adjm[0][1]=-((mat[0][1]*mat[2][2])-(mat[2][1]*mat[0][2]));
                adjm[1][1]=(mat[0][0]*mat[2][2])-(mat[2][0]*mat[0][2]);
                adjm[2][1]=-((mat[0][0]*mat[2][1])-(mat[2][0]*mat[0][1]));
                adjm[0][2]=(mat[0][1]*mat[1][2])-(mat[1][1]*mat[0][2]);
                adjm[1][2]=-((mat[0][0]*mat[1][2])-(mat[1][0]*mat[0][2]));
                adjm[2][2]=(mat[0][0]*mat[1][1])-(mat[1][0]*mat[0][1]);
    }
    if(odr==2)
    {
        adjm2[0][0]=mat2[1][1];
        adjm2[1][1]=mat2[0][0];
        adjm2[0][1]=-mat2[0][1];
        adjm2[1][0]=-mat2[1][0];
    }
}
/**
 * This function performs arithmetic operations on matrices of size 2x2 or 3x3.
 */
void arth()
{
    char opr='-';
    double mata[3][3],mata2[2][2],amata[3][3],amata2[2][2];
    
    if(odr==2)
    {
        while(!(opr=='+'||opr=='-'))
        {
            std::cout<<"Enter the Operator : ";std::cin>>opr;
            if(!(opr=='+'||opr=='-'))
               {
                   HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,4);std::cout<<"Invalid Operator!"<<std::endl;SetConsoleTextAttribute(h,15);
               }
        }
        std::cout<<"Enter the Matrix : ";
        for(int i=0; i<odr;i++)
            {
                std::cout<<"_______Row "<<i+1<<"_______"<<std::endl;
                for(int j=0; j<odr;j++)
                {
                    std::cout <<"Enter element "<<j+1<<" : ";std::cin>>mata2[i][j];
                }
            }
            show(odr,mat,mat2);
            std::cout<<"        "<<opr<<"       "<<std::endl;
            show(odr,mata,mata2);
            std::cout<<"        =       "<<std::endl;
            switch(opr)
            {
                case '+': for(int i=0;i<odr;i++)
                            {
                                for(int j=0;j<odr;j++)
                                {
                                    amata2[i][j]=mata2[i][j] + mat2[i][j];
                                }
                            }
                            break;
                case '-': for(int i=0;i<odr;i++)
                            {
                                for(int j=0;j<odr;j++)
                                {
                                    amata2[i][j]=mata2[i][j] - mat2[i][j];
                                }
                            }
                            break;
            }

    }

    if(odr==3)
    {
        while(!(opr=='+'||opr=='-'))
        {
            std::cout<<"Enter the Operator : ";std::cin>>opr;
            if(!(opr=='+'||opr=='-'))
               {
                   HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,4);std::cout<<"Invalid Operator!"<<std::endl;SetConsoleTextAttribute(h,15);
               }
        }
        std::cout<<"Enter the Matrix : ";
        for(int i=0; i<odr;i++)
            {
                std::cout<<"_______Row "<<i+1<<"_______"<<std::endl;
                for(int j=0; j<odr;j++)
                {
                    std::cout <<"Enter element "<<j+1<<" : ";std::cin>>mata[i][j];
                }
            }
            show(odr,mat,mat2);
            std::cout<<"            "<<opr<<"           "<<std::endl;
            show(odr,mata,mata2);
            std::cout<<"            =           "<<std::endl;
            switch(opr)
            {
                case '+': for(int i=0;i<odr;i++)
                            {
                                for(int j=0;j<odr;j++)
                                {
                                    amata[i][j]=mata[i][j] + mat[i][j];
                                }
                            }
                            break;
                case '-': for(int i=0;i<odr;i++)
                            {
                                for(int j=0;j<odr;j++)
                                {
                                    amata[i][j]=mat[i][j] - mata[i][j];
                                }
                            }
                            break;
    }
    }

        std::cout<<std::endl;
            show(odr ,amata,amata2);

}

int main()
{
    char dec='q';
    int N;
    double detr;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,11);
    std::cout<<"Code by Umer Ghafoor"<<std::endl;
    SetConsoleTextAttribute(h,15);
while (dec!='e')
{
    std::string resp_inv;
    std::cout<<";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;MATRIX CALCULATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"<<std::endl;
    std::cout<<"Enter the Order of matrix : ";std::cin>>odr;
    if(odr==2 || odr==3){}
    else{HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,4);std::cout<<"Invalid matrix!"<<std::endl;SetConsoleTextAttribute(h,15);continue;}
    switch(odr)
    {
    case 3:
            for(int i=0; i<3;i++)
            {
                std::cout<<"_______Row "<<i+1<<"_______"<<std::endl;
                for(int j=0; j<3;j++)
                {
                    std::cout <<"Enter element "<<j+1<<" : ";std::cin>>mat[i][j];
                }
            }
            break;
    case 2:
            for(int i=0; i<2;i++)
            {
                std::cout<<"_______Row "<<i+1<<"_______"<<std::endl;
                for(int j=0; j<2;j++)
                {
                    std::cout <<"Enter element "<<j<<" : ";std::cin>>mat2[i][j];
                }
            }
            break;
    }
    std::cout<<std::endl;
    show(odr,mat,mat2);
    std::cout<<"y to continue ";std::cin>>dec;
    system("cls");
//__________________________________________________________________________________________________________________

adj(odr,mat,mat2);
//__________________________________________________________________________________________________________________Inverse
    //invr(odr,mat,mat2);
    detr=det(odr,mat,mat2);
    if(detr!=0)
    {
        if(odr==3)
        {
                for(int i=0; i<odr;i++)
                {
                    for(int j=0;j<odr;j++)
                    {
                        invr[i][j]=adjm[i][j]/detr;
                    }
                }
        }
    if(odr==2)
        {
                for(int i=0; i<odr;i++)
                {
                    for(int j=0;j<odr;j++)
                    {
                        invr2[i][j]=adjm2[i][j]/detr;
                    }
                }
        }
    }
    else{resp_inv="does not exist";}
while(dec!='n')
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,03);
std::cout<<"======================================================================================="<<std::endl;
std::cout<<"|\t1. To display a matrix"<<std::endl;
std::cout<<"|\t2. To check whether the entered matrix is symmetric matrix or not"<<std::endl;
std::cout<<"|\t3. To check whether the entered matrix is identity matrix or not"<<std::endl;
std::cout<<"|\t4. To determine the determinant of entered matrix"<<std::endl;
std::cout<<"|\t5. To determine the adjoint of entered matrix"<<std::endl;
std::cout<<"|\t6. To determine the inverse of entered matrix"<<std::endl;
std::cout<<"|\t7. To determine the solution of entered matrix (i.e. solving multiple linear equations simultaneously)"<<std::endl;
std::cout<<"|\t8. To Arthmatic"<<std::endl;
std::cout<<"======================================================================================="<<std::endl;
    SetConsoleTextAttribute(h,15);

    std::cout<<"Enter the task : ";
    std::cin>>N;

std::cout<<"======================================================================================="<<std::endl;
    switch(N)
    {
        case 1:std::cout<<"Matrix is "<<std::endl;show(odr,mat,mat2);break;
        case 2:show(odr,mat,mat2);sym(odr,mat,mat2);break;
        case 3:show(odr,mat,mat2);id(odr,mat,mat2);break;
        case 4:show(odr,mat,mat2);std::cout<<"Determinent of the matrix = "<<det(odr,mat,mat2)<<std::endl;break;
        case 5:adj(odr,mat,mat2);std::cout<<"Adjoint of the matrix is "<<std::endl;show(odr,adjm,adjm2);break;
        case 6:{std::cout<<"Inverse of the matrix ";;if(detr!=0){std::cout<<std::endl;show(odr,invr,invr2);}else{HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,4);std::cout<<resp_inv<<std::endl;}SetConsoleTextAttribute(h,15);break;}
        case 7:std::cout<<"------------------------------Equation solver------------------------------ "<<std::endl;
                if(detr!=0){solve(odr,mat,mat2);}else {HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleTextAttribute(h,4);std::cout<<"The solution "<<resp_inv<<std::endl;SetConsoleTextAttribute(h,15);}break;
        case 8:arth();break;
    }
    std::cout<<"y to continue / n to exit ";std::cin>>dec;
    system("cls");
}
std::cout<<"------------------_-----------_-------------------"<<std::endl;
std::cout<<"-----------------_-_---------_-_------------------"<<std::endl;
std::cout<<"----------------_---_-------_---_-----------------"<<std::endl;
std::cout<<"---------------_-----_-----_-----_----------------"<<std::endl;
std::cout<<"--------------_-------_---_-------_---------------"<<std::endl;
std::cout<<"-------------_---------_-_---------_--------------"<<std::endl;
std::cout<<"------------_-----------_-----------_-------------"<<std::endl;
std::cout<<"-----------_-------------------------_------------"<<std::endl;
std::cout<<"----------_---------------------------_-----------"<<std::endl;
std::cout<<"---------_-----------------------------_----------"<<std::endl;
std::cout<<"--------_-------------------------------_---------"<<std::endl;
std::cout<<"y to start over / e to exit ";std::cin>>dec;
}
}