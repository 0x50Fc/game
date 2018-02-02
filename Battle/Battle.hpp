//
//  Battle.hpp
//  KKGame
//
//  Created by hailong11 on 2017/12/15.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef Battle_hpp
#define Battle_hpp

#if defined(TARGET_OS_IOS)
#include <KKGame/kk-game.h>
#endif

/**
 * 对战游戏
 */
namespace kk {
    
    namespace battle {
        
        
        /**
         * 场景数据模型
         */
        class BTSceneElement: public kk::game::GMSceneElement {
            DEF_CLASS(BTSceneElement)
        public:
            virtual ~BTSceneElement();
            virtual kk::gl::vec2& size();
            virtual void setSize(kk::gl::vec2& v);
            
            virtual void init();
            
        protected:
            kk::gl::vec2 _size;
        };
        
    }
    
}

#endif /* Battle_hpp */
