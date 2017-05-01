#include "ChainListOfMovieEvent.hpp"



ChainListOfMovieEvent::ChainListOfMovieEvent()
{
    first = NULL;
}


ChainListOfMovieEvent::~ChainListOfMovieEvent()
{
    EltMovieEvent *p1 = first;
    EltMovieEvent *p2 = first;
    while (p1 != NULL) {
        p2 = p2->next;
        delete p1;
        p1 = p2;
    }
}


void ChainListOfMovieEvent::AddElement(MovieEvent *_movieEvent, int _ME_type)
{
    EltMovieEvent *p = first;
    EltMovieEvent *newElt = new EltMovieEvent;
    newElt->theMovieEvent = _movieEvent;
    newElt->ME_type = _ME_type;
    newElt->next = NULL;
    if (p == NULL) {
        first = newElt;
    } else {
        while (p->next!=NULL) { p=p->next; }
        p->next = newElt;
    }
}


MovieEvent *ChainListOfMovieEvent::GetElement(long int index)
{
    EltMovieEvent *p = first;
    long int cursor = 0;
    while ((p!=NULL) && (cursor < index)) {
        p=p->next;
        cursor++;
    }
    if (p != NULL) { return p->theMovieEvent; }
    return NULL;
}

//                     Voklaron McChaussette
//Qui est donc cet �tre myst�rieux? Sa tombe orne le cimeti�re de PruPraProk,
//marqu�e d'une p�riode de temps absurde.
//Est-ce un h�ros? Un fou? un clin d'oeil � quelque chose
//que vous ne pouvez pas comprendre?
//La suite vous r�v�lera-t-elle plus de secrets � propos de cette homme?
//Y'aura-t-il m�me une suite? Et est-ce qu'il s'appelle VRAIMENT Voklaron McChaussette?
//Un pr�nom pareil, �a n'existe pas.
//Mais comment faire la diff�rence entre quelque chose
//qui existe et quelque chose qui n'existe pas quand on est dans une histoire?
//Etrangitude, Insolit�e, Bizarration...

long int ChainListOfMovieEvent::GetQtyOfElement(int ME_typeToCount)
{
    long int qty = 0;
    EltMovieEvent *p = first;
    while (p!=NULL) {
        if ((p->ME_type == ME_typeToCount) || (ME_typeToCount == ME_TYPE_ALL)) { qty++; }
        p = p->next;
    }
    return qty;
}


MovieEvent **ChainListOfMovieEvent::ExtractListOfMovieEvent(int ME_typeToGet,
                                                            long int *qtyExtracted)
{
    MovieEvent **ListOfMovieEventExtracted;
    long int qtyToExtract = GetQtyOfElement(ME_typeToGet);
    if (qtyExtracted != NULL) { *qtyExtracted = qtyToExtract; }

    if (qtyToExtract != 0)
    {
        ListOfMovieEventExtracted = new MovieEvent *[qtyToExtract];
        EltMovieEvent *p = first;
        int index = 0;
        while (p!=NULL) {
            if ((p->ME_type == ME_typeToGet) || (ME_typeToGet == ME_TYPE_ALL)) {
                ListOfMovieEventExtracted[index] = p->theMovieEvent;
                index++;
            }
            p = p->next;
        }
        return ListOfMovieEventExtracted;
    }
    return NULL;
}


MovieEvent **ChainListOfMovieEvent::ExtractAndDefineListOfBreakPoint(long int *qtyExtracted)
{
    long int qtyOfImgEvent = 0;
    long int qtyOfSoundEvent = 0;
    MovieEvent **ListOfMovieEventExtracted;
    long int qtyInChainList = GetQtyOfElement(ME_TYPE_BREAKPOINT);

    if (qtyInChainList != 0)
    {
        ListOfMovieEventExtracted = new MovieEvent *[qtyInChainList];
        EltMovieEvent *p = first;
        ME_BreakPoint *breakPointToAdd;
        long int lastBreakPtImgIndex;
        long int lastBreakPtSoundIndex;
        long int qtyPutInList = 0;
        int gotABreakPoint = 0;
        long int addedBreakPtTime = -1;

        //l'extraction permet d'�viter un tas de conneries, � savoir :
        // - les breakpoint en fin de film,
        // - deux breakpoint qui se suivent dans la liste (m�me si leur dates sont diff�rentes.
        // - deux breakpoint non cons�cutifs, mais qui ont la m�me date.
        while (p!=NULL)
        {
            if (p->ME_type == ME_TYPE_BREAKPOINT) {
                if (!gotABreakPoint && (p->theMovieEvent->GetActTime() != addedBreakPtTime)) {
                    breakPointToAdd = (ME_BreakPoint *) (p->theMovieEvent);
                    lastBreakPtImgIndex = qtyOfImgEvent;
                    lastBreakPtSoundIndex = qtyOfSoundEvent;
                    gotABreakPoint = 1;
                }
            } else {
                if (gotABreakPoint) {
                    breakPointToAdd->SetCursors(lastBreakPtImgIndex, lastBreakPtSoundIndex);
                    ListOfMovieEventExtracted[qtyPutInList] = breakPointToAdd;
                    qtyPutInList++;
                    addedBreakPtTime = breakPointToAdd->GetActTime();
                    gotABreakPoint = 0;
                }
                if (p->ME_type == ME_TYPE_IMAGE) {
                    qtyOfImgEvent++;
                } else if (p->ME_type == ME_TYPE_SOUND) {
                    qtyOfSoundEvent++;
                }
            }
            p = p->next;
        }
        if (qtyExtracted != NULL) { *qtyExtracted = qtyPutInList; }
        return ListOfMovieEventExtracted;
    }
    if (qtyExtracted != NULL) { *qtyExtracted = 0; }
    return NULL;
}


//�a trie la liste de MovieEvent dans l'ordre chronologique (la valeur time).
//le premier MovieEvent n'est pas tri�, il reste toujours le premier.
//on consid�re que le premier MovieEvent est toujours le BreakPoint de d�part.
void ChainListOfMovieEvent::SortList()
{
    if (first == NULL) { return; }

    EltMovieEvent *p;
    EltMovieEvent *precedentOfP;
    EltMovieEvent *lastEltOfSortedList = first;
    EltMovieEvent *eltWithMinTime;
    EltMovieEvent *eltPrecedentOfEltWithMinTime;
    long int minTime = 0;

    while (lastEltOfSortedList->next != NULL) {
        p = lastEltOfSortedList->next;
        eltWithMinTime = p;
        minTime = p->theMovieEvent->GetActTime();
        eltPrecedentOfEltWithMinTime = p;
        precedentOfP = p;
        p = p->next;

        //trouvage du minimum
        while (p != NULL) {
            if (p->theMovieEvent->GetActTime() < minTime) {
                minTime = p->theMovieEvent->GetActTime();
                eltWithMinTime = p;
                eltPrecedentOfEltWithMinTime = precedentOfP;
            }
            precedentOfP = p;
            p = p->next;
        }

        //�changeage entre le minimum et le premier �l�ment de la liste non tri�e,
        //si n�cessaire.
        if (eltWithMinTime != lastEltOfSortedList->next) {
            eltPrecedentOfEltWithMinTime->next = eltPrecedentOfEltWithMinTime->next->next;
            eltWithMinTime->next = lastEltOfSortedList->next;
            lastEltOfSortedList->next = eltWithMinTime;
        }

        //avan�age d'un cran, et on recommence � trier avec ce qui reste.
        lastEltOfSortedList = lastEltOfSortedList->next;
    }
}


long int ChainListOfMovieEvent::ConcatListOfMovieEvent(ChainListOfMovieEvent *chainListToAdd,
                                                       long int timeToAdd,
                                                       long int durationOfConcatenation/* = -1*/)
{
    MovieEvent *movieEventToAdd;
    int ME_TypeToAdd;
    EltMovieEvent *p = chainListToAdd->first;
    long int durationAdded = 0;

    while ((p != NULL)
           && (
                (durationOfConcatenation == -1)
                || (p->theMovieEvent->GetActTime() <= durationOfConcatenation)
           ))
    {
        movieEventToAdd = p->theMovieEvent->Copy(timeToAdd);
        ME_TypeToAdd = p->ME_type;
        this->AddElement(movieEventToAdd, ME_TypeToAdd);
        durationAdded = p->theMovieEvent->GetActTime();
        p = p->next;
    }

    if (durationOfConcatenation != -1) { return durationOfConcatenation; }
    return durationAdded;
}


//� mettre en commentaire apr�s. C'est juste pour tester si la liste d'�v�nement est bien.
/*void ChainListOfMovieEvent::WriteListOfTimeForTest()
{
    EltMovieEvent *p = first;
    cout << "la liste : ";
    while (p!=NULL) {
        cout << p->theMovieEvent->GetActTime() << "  ";
        p = p->next;
    }
    cout << endl;
}*/

void ChainListOfMovieEvent::DeleteAllEvents()
{
    EltMovieEvent *p = first;
    while (p!=NULL) {
        delete p->theMovieEvent;
        p = p->next;
    }
}
