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


#endif // dbg_hpp