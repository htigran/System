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
    #define DBG_MESSAGE(A) std::cout << A << std::endl;
#else
    #define DBG_MESSAGE(A)
#endif /* dbg_hpp */


#endif // dbg_hpp