//
//  dbg.hpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#ifndef PLATFORM_DBG_INC_DBG_HPP_
#define PLATFORM_DBG_INC_DBG_HPP_

#define DEBUG 1

// TRACES show the control follow of the software for debugging purposes
#if DEBUG == 1
#define TRACE(A) std::cout << A << std::endl;
#else
#define TRACE(A)
#endif

#endif // PLATFORM_DBG_INC_DBG_HPP_
