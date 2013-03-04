# include "dxf_2D.h"

line :: line () : base ()
{
}


void line :: set ( string entitySubType, double x1, double y1, double x2, double y2)
{
	base :: set ( entitySubType, x1, y1, x2, y2 );
}


void line :: intermediate()
{
	if ( entityType == "rectangle" || entityType == "Rectangle")
		write_Entity();
	else
		write_Common_Part_Entity ();
}


void line :: write_Common_Part_Entity ()
{	
	writeFile << " LINE \n 5 \n 43 \n 100 \n AcDbEntity \n 100 "
		"\n AcDbLine \n 8 \n 0 \n 62 \n 0 \n 256 \n 370 \n "
		" -1 \n 6 \n ByLayer";
	write_Input_Part_Entity ();
}

void line :: write_Input_Part_Entity ()
{
	if ( (entityType == "Vertical") || (entityType == "vertical") )
	{ 	
			length = xEnd;
			xEnd = xStart ;
			yEnd = (yStart + length) ;
			writeFile << "\n 10 \n " << xStart << 
				" \n 20 \n " << yStart << 
				" \n 30 \n 0.0 "
				" \n 11 \n " << xEnd << 
				" \n 21 \n " << yEnd <<
				" \n 31 \n 0.0 "
				" \n 0 " ;
	}
	else if  ( (entityType == "Horizontal") || (entityType == "horizontal") )
	{ 
			xEnd += xStart;
			yEnd = yStart ;
			writeFile << "\n10 \n " << xStart <<
 				" \n  20 \n " << yStart << 
				" \n 11 \n " << xEnd << 
				" \n 21 \n " << yEnd << 
				"  \n 0" ;			
	}
	else
	{	
			writeFile << " \n 10 \n " << xStart <<
				 " \n  20 \n " << yStart << 
				 " \n 30 \n 0.0 "
				 " \n 11 \n " << xEnd << 
				 " \n 21 \n " << yEnd <<
				 " \n 0" ;
	}
}

void line :: write_Entity ()
{
	writeFile <<  " LWPOLYLINE \n 5 \n 43 \n 330 \n 1F \n 100 "
		" \n AcDbEntity \n 8 \n 0 \n 100 \n AcDbPolyLine "
		" \n 90 \n 4 \n 70 \n 1 \n 43 \n 0.0" 
		" \n 10 \n "<< xStart << 
		" \n 20 \n " << yStart << 
		" \n 10 \n " << xStart <<
		" \n 20 \n " <<  yEnd << 
		" \n 10 \n " << xEnd <<
		" \n 20 \n " << yEnd << 
		" \n 10 \n "<< xEnd << 
		" \n 20 \n " <<yStart<< 
		" \n " ;
	}

void line :: draw ( string fileName)
{
	dxfFileName = fileName ;
	writeFile.open( dxfFileName.c_str() ) ;
	read_Header ();
	intermediate();
	read_Footer();
	writeFile.close () ;
}

