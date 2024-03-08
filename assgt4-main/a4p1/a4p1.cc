#include <iostream>
#include <string>
#include <cassert>
#include "a4p1.h"

using namespace std;

void Q_init (Queue& q) {
    q.first = nullptr;
    q.last = nullptr;
}

bool Q_isEmpty (const Queue& q) {
    return nullptr == q.first;
}

void Q_enter (Queue& q, string val) {
    Qnode* p = new Qnode {};
    p -> val = val;
    p -> next = nullptr;
    if(Q_isEmpty(q)) {
        q.first = p;
    }
    else {
        q.last -> next = p;
    }
    q.last = p;
}

string Q_first (const Queue& q) { 
    assert(!Q_isEmpty(q));
    return q.first -> val;
}

void Q_leave (Queue& q) {
    assert(!Q_isEmpty(q));
    Qnode *p = q.first;
    q.first = q.first -> next;
    if(nullptr == q.first) {
        q.last = nullptr;
    }
    delete p;
}

void Q_nuke (Queue& q) {
    while(!Q_isEmpty(q)) {
        Q_leave(q);
    }
} 

void PQ_init (PQ& pq) { 
    pq = nullptr;
}

bool PQ_isEmpty (const PQ& pq) {
    return pq == nullptr;
}

void PQ_enter (PQ& pq, std::string val, int priority) {
    // If it needs to be added to the front
    if (pq == nullptr || pq->priority > priority) {
        PQnode* newPQ = new PQnode {};
        newPQ->priority = priority;
        Q_init(newPQ->q);
        Q_enter(newPQ->q, val);
        newPQ->next = pq;
        pq = newPQ;
    } else { // Else find the pos for it to be added to
        PQnode* cur = pq;

        while (cur != nullptr && cur -> next != nullptr && cur-> next -> priority <= priority) {
            cur = cur->next;
        }

        if (cur->priority == priority) {
            // Existing priority
            Q_enter(cur -> q, val);
        } else {
            // Create a new PQnode to be inserted
            PQnode* newPQ = new PQnode {};
            newPQ->priority = priority;
            Q_init(newPQ->q);
            Q_enter(newPQ->q, val);
            cur -> next = newPQ; 
        }
    }
}

string PQ_first (const PQ& pq) {
    if (pq == nullptr || pq->q.first == nullptr) {
        std::cerr << "Error, priority queue is empty." << std::endl;
        exit(1);
    }

    return pq -> q.first -> val;
}

void PQ_leave (PQ& pq) {
    // Cases: PQ is empty, PQ node only has one in queue and needs to be deleted, PQ node has more than one in queue
    if(PQ_isEmpty(pq)){
        cerr << "Error, priority queue is empty." << endl;
        exit(1);
    }

    Q_leave(pq->q);

    // Check whether the queue within the PQnode is now empty
    if (pq->q.first == nullptr) {
        PQnode* temp = pq;
        pq = pq->next;
        Q_nuke(temp->q);
        delete temp;
    }
}

int PQ_size (const PQ& pq) {
    int size = 0;
    PQnode* curPQ = pq;
    Qnode* curQ = nullptr;
    while(curPQ != nullptr) {
        curQ = curPQ -> q.first;
        while(curQ != nullptr) {
            size++;
            curQ = curQ -> next;
        }
        curPQ = curPQ -> next;
    }

    return size;
}

int PQ_sizeByPriority (const PQ& pq, int priority) {
    int size = 0;
    PQnode* curPQ = pq;

    while(curPQ != nullptr) {
        if(curPQ -> priority == priority) {
            Qnode* curQ = curPQ -> q.first;
            while(curQ != nullptr) {
                size++;
                curQ = curQ -> next;
            }
        }
        curPQ = curPQ -> next;
    }

    return size;
}

int PQ_numPriorities (const PQ& pq) {
    int size = 0;
    PQnode* curPQ = pq;

    while(curPQ != nullptr && !PQ_isEmpty(curPQ)) {
        size++;
        curPQ = curPQ -> next;
    }

    return size;
}

void PQ_nuke(PQ& pq) {
    while (!PQ_isEmpty(pq)) {
        PQ_leave(pq);
    }
}
