#include "ME_BreakPoint.hpp"



ME_BreakPoint::ME_BreakPoint(long int _actTime, int _breakPointLevel,
                             long int _cursorME_Image = 0, long int _cursorME_Sound = 0)
    : MovieEvent(_actTime)
{
    cursorME_Image = _cursorME_Image;
    cursorME_Sound = _cursorME_Sound;
    breakPointLevel = _breakPointLevel;
}


ME_BreakPoint::~ME_BreakPoint()
{
}


void ME_BreakPoint::Act()
{
}

//Allez une petite énigme amusante. Il est possible d'exécuter l'application splash.exe
//dans un certain contexte, de façon à ce qu'elle n'affiche qu'un gros point d'exclamation rouge.
//Comment faire?
//Bon c'est pas bien dur. Je vous laisse trouver tout seul.

MovieEvent *ME_BreakPoint::Copy(long int timeToAdd)
{
	return (MovieEvent *) new
        ME_BreakPoint(actTime+timeToAdd, breakPointLevel, cursorME_Image, cursorME_Sound);
}


void ME_BreakPoint::SetCursors(long int _cursorME_Image, long int _cursorME_Sound)
{
    cursorME_Image = _cursorME_Image;
    cursorME_Sound = _cursorME_Sound;
}

long int ME_BreakPoint::GetActTime() { return actTime; }

long int ME_BreakPoint::GetCursorMe_Image() { return cursorME_Image; }

long int ME_BreakPoint::GetCursorMe_Sound() { return cursorME_Sound; }

int ME_BreakPoint::GetLevel() { return breakPointLevel; }

