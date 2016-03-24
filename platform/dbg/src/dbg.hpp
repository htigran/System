//
//  dbg.hpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#ifndef dbg_hpp
#define dbg_hpp

#if DEBUG == 1
    #define TRACE(A) std::cout << A << std::endl;
#else
    #define TRACE(A)
#endif /* dbg_hpp */

#define SAFE(A) \
if ((A) == -1) { \
std::cerr << "tsocket error" << __LINE__ << std::endl; \
exit(5); \
}

#endif // dbg_hpp
