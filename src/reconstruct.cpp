#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


ifstream fin;
ofstream fout;
typedef vector <string> VS;
VS line;

#define maxn 100001
#define BUF_NUM 10000000
#define REQ_NUM 100000
#define P_NUM 100
#define TAG 1
	
string my_itos(int i)
{
        string r;
        char c[128];

        sprintf(c, "%d\0", i);
        r += c;

        return r;
}


string getPara(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=',')
		end++;
	return a.substr(start, end - start + 1);
}

string getPurePara(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;	
	while (a[end]!=',')
		end++;
	while (a[start]!='=')
		start++;
	return a.substr(start+1, end - start - 1);
}


string getTime(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=']')
		end++;
	return a.substr(start, end - start + 1);
}

void readfile()
{
	string s;
	
	getline(fin ,s);
	line.clear();
	while (fin)
	{
		line.push_back(s);
		getline(fin ,s);		
	}
}


void init()
{

	readfile();
}


void make()
{
	fout << "#include \"mpi.h\"" << endl;
	fout << "#include <string.h>" << endl;
	fout << "#include <stdio.h>" << endl;
	fout << endl;
	fout << "#define DELAY 1" << endl;
	fout << endl;
	
	fout << "int main(int argc,char *argv[])" << endl;
	fout << "{" << endl;
	fout << "\tint myid, numprocs;" << endl;
	fout << "\tint dst, src;" << endl;
	fout << "\tchar buf[" << BUF_NUM << "];" << endl;
	fout << "\tchar buf2[" << BUF_NUM << "];" << endl;
	fout << "\tint displs[" << P_NUM << "];" << endl;
	fout << "\tint displs2[" << P_NUM << "];" << endl;
	fout << "\tMPI_Status status;" << endl;
	fout << "\tMPI_Request request;" << endl;
	fout << "\tMPI_Status arr_status[" << REQ_NUM << "];" << endl;
	fout << "\tMPI_Request arr_request[" << REQ_NUM << "];" << endl;
	fout << endl;
	
	fout << "\tMPI_Init(&argc,&argv);" << endl;
    fout << "\tMPI_Comm_size(MPI_COMM_WORLD,&numprocs);" << endl;
    fout << "\tMPI_Comm_rank(MPI_COMM_WORLD,&myid);" << endl;
	fout << "\tfprintf(stdout,\"Process %d of %d\\n\",myid, numprocs);" << endl;
	fout << "\tfprintf(stdout,\"Skeleton Program.\\n\");" << endl;
	fout << "\tmemset(displs,0,sizeof(displs));" << endl;
	fout << "\tmemset(displs2,0,sizeof(displs2));" << endl;
	fout << endl;

	{
		string cir;
		string func;
		int i, j, n, cId = 0, cTimes, cLen;
		int nProc;		
		
		n = line.size();
		nProc = atoi(getPurePara(line[0],"same=").c_str());
		
		for (i=0;i<n;i++)
		{
			
			if (line[i].find("FOR TIMES") != string::npos)
			{
				cir = getPara(line[i], "TIMES");
				cTimes = atoi(cir.substr(6,cir.length()-6).c_str());
				cir = getPara(line[i], "CLEN");
				cLen = atoi(cir.substr(4,cir.length()-4).c_str());
				fout << "\tfor(int c" << cId << "=1; c" << cId << "<=" << cTimes << "; c" << cId << "++ ){" << endl;
				cId++;
			}

			
			func = getPurePara(line[i], "func");
			
			
			if (func == "MPI_Send")
			{				
				//int MPI_Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)				
				fout << "\tdst = myid;" << endl;
				fout << "\tMPI_Send(buf, ";
				fout << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", dst, " << TAG << ", " << "MPI_COMM_WORLD);" << endl;
			}
			
			if (func ==  "MPI_Recv")
			{
				//int MPI_Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, 
				//	MPI_Comm comm, MPI_Status *status)
				fout << "\tsrc = myid;" << endl;
				fout << "\tMPI_Recv(buf, ";
				fout << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", src, " << TAG << ", " << "MPI_COMM_WORLD, &status);" << endl;
			}
			if (func ==  "MPI_Isend")
			{
				//int MPI_Isend(void* buf, int count, MPI_Datatype datatype, int dest, int tag,
				//	MPI_Comm comm, MPI_Request *request);
				fout << "\tdst = myid;" << endl;
				fout << "\tMPI_Isend(buf, ";
				fout << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", dst, " << TAG << ", " << "MPI_COMM_WORLD, &request);" << endl;
			}
			if (func == "MPI_Irecv")
			{
				//int MPI_Irecv(void* buf, int count, MPI_Datatype datatype, int source, int tag,
				//	MPI_Comm comm, MPI_Request *request);
				fout << "\tsrc = myid;" << endl;
				fout << "\tMPI_Irecv(buf, ";
				fout << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", src, " << TAG << ", " << "MPI_COMM_WORLD, &request);" << endl;
			}
			if (func == "MPI_Wait")
			{
				//int MPI_Wait(MPI_Request *request, MPI_Status *status);
				fout << "\tMPI_Wait(&request, &status);" << endl;
			}
			if (func == "MPI_Waitall")
			{
				//int MPI_Waitall(int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses);
				fout << "\tMPI_Waitall(";
				fout << getPurePara(line[i], "count") << ", arr_request, arr_status);" << endl;
			}
			if (func ==  "MPI_Bcast")
			{
				//int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype, int root, MPI_Comm comm);
				fout << "\tMPI_Bcast(buf, " << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", ";
				fout << getPurePara(line[i], "root") << ", MPI_COMM_WORLD);" << endl;
			}
			if (func == "MPI_Alltoall")
			{
				//int MPI_Alltoall(void* sendbuf, int sendcount, MPI_Datatype sendtype,
				//	void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
				fout << "\tMPI_Alltoall(buf, " << getPurePara(line[i], "sendcount") << ", ";
				fout << getPurePara(line[i], "sendtype") << ", buf2, ";
				fout << getPurePara(line[i], "recvcount") << ", ";
				fout << getPurePara(line[i], "recvtype") << ", MPI_COMM_WORLD);" << endl;
			}
			if (func == "MPI_Alltoallv")
			{
				//int MPI_Alltoallv(void* sendbuf, int *sendcounts, int *sdispls,
				//MPI_Datatype sendtype, void* recvbuf, int *recvcounts, int *rdispls,
				//MPI_Datatype recvtype, MPI_Comm comm);				
				fout << "\tMPI_Alltoallv(buf, " << getPurePara(line[i], "sendcounts") << ", displs, ";
				fout << getPurePara(line[i], "sendtype") << ", buf2, ";
				fout << getPurePara(line[i], "recvcounts") << ", displs2, ";
				fout << getPurePara(line[i], "recvtype") << ", MPI_COMM_WORLD);" << endl;
			}
			if (func == "MPI_Reduce")
			{
				//int MPI_Reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
				//	MPI_Op op, int root, MPI_Comm comm);
				fout << "\tMPI_Reduce(buf, buf2, ";
				fout << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", ";
				fout << getPurePara(line[i], "op") << ", ";
				fout << getPurePara(line[i], "root") << ", MPI_COMM_WORLD);" << endl;
			}
			if (func == "MPI_Allreduce")
			{
				//int MPI_Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
				//	MPI_Op op, MPI_Comm comm);
				fout << "\tMPI_Allreduce(buf, buf2, ";
				fout << getPurePara(line[i], "count") << ", ";
				fout << getPurePara(line[i], "datatype") << ", ";
				fout << getPurePara(line[i], "op") << ", MPI_COMM_WORLD);" << endl;				
			}
			if (func == "MPI_Barrier")
			{
				//int MPI_Barrier(MPI_Comm comm);
				fout << "\tMPI_Barrier(MPI_COMM_WORLD);" << endl;
			}
			if (func == "MPI_Comm_split")
			{
				;
			}
			if (func == "MPI_Comm_dup")
			{
				;
			}
			
			if (line[i].find("FOR END") != string::npos)
			{
				fout << "\t}" << endl;
			}
			
			//Delay Time
			{
				double t = 0, dt;
				int posi = 0;
				
				for (j=0;j<nProc;j++)
				{
					posi = line[i].find("Blank");
					sscanf(line[i].substr(posi+7,cir.length()-posi-7).c_str(), "%lf", &dt);
					t += dt;
				}
				if (dt > 1e-6) 
				{
					t/=nProc;
				}
				else
				{
					;
				}
				cTimes = int(t);
				fout << "\t/*Delay*/ for(int d=1; d<=" << cTimes << "; d++ ){}" << endl;				
			}
			
		}
	}
	
	fout << "\tMPI_Finalize();" << endl;
	fout << "\treturn 0;" << endl;
	fout << "}" << endl;
}

int main(int argc,char *argv[])
{
  //  char ts1[16] = "IScircle.txt";
	//char ts2[16] = "ISskeleton.txt";
	
	
	
	
	if (argc != 3)
    {
        cout << "Usage: reconstruct inputfile outputfile\n" << endl;
        return 0;		
    }
	
	
	fin.open(argv[1]);
	//fin.open(ts1);
	fout.open(argv[2]);
	//fout.open(ts2);
	
    init();
	
	fin.close();
	
	make();
	
	fout.close();
    return 0;
}
