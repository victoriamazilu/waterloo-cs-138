#include <string>

/* ************************************************************** */
// Struct definitions and function declarations for Queue
// -----------------------------------------------------------------
struct Qnode {
    std::string val;
    Qnode* next;
};
struct Queue {
    Qnode* first;
    Qnode* last;
};

void Q_init (Queue& q);
bool Q_isEmpty (const Queue& q);
void Q_enter (Queue& q, std::string val);
std::string Q_first (const Queue& q);
void Q_leave (Queue& q);
void Q_nuke (Queue& q);
/* ************************************************************** */



/* ************************************************************** */
// Struct definitions and function declarations for PQ
// -----------------------------------------------------------------
struct PQnode {
    int priority;
    Queue q;
    PQnode* next;
};
typedef PQnode* PQ;

void PQ_init (PQ& pq);
bool PQ_isEmpty (const PQ& pq);
void PQ_enter (PQ& pq, std::string val, int priority);
std::string PQ_first (const PQ& pq);
void PQ_leave (PQ& pq);
int PQ_size (const PQ& pq);
int PQ_sizeByPriority (const PQ& pq, int priority);
int PQ_numPriorities (const PQ& pq);
void PQ_nuke (PQ & pq);
/* ************************************************************** */
