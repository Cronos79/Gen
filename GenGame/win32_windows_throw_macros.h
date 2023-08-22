/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#pragma once

#define GENWND_EXCEPT( hr ) win32_window::HrException( __LINE__,__FILE__,(hr) )
#define GENWND_LAST_EXCEPT() win32_window::HrException( __LINE__,__FILE__,GetLastError() )