//
//  kk-ui.hpp
//  KKGame
//
//  Created by hailong11 on 2017/12/18.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_ui_hpp
#define kk_ui_hpp

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-gl.h>
#endif

namespace kk {
    
    namespace ui {
        
        struct UITouch {
        public:
            UITouch():id(0),loc(0){}
            kk::Int id;
            kk::gl::vec3 loc;
        };
        
        enum PixelType {
            PixelTypeAuto,PixelTypePercent,PixelTypePX,PixelTypeRPX
        };
        
        struct Pixel {
        public:
            Pixel():value(0),type(PixelTypeAuto){}
            kk::Float value;
            PixelType type;
        };

        struct Edge {
        public:
            Edge():left(),right(),top(),bottom(){}
            Pixel top;
            Pixel right;
            Pixel bottom;
            Pixel left;
        };
        
        class PixelProperty : public kk::TProperty<Pixel&> {
        public:
            PixelProperty(Named * name, Getter getter, Setter setter);
            virtual void def(ScriptContext ctx);
        };
        
        class EdgeProperty : public kk::TProperty<Edge&> {
        public:
            EdgeProperty(Named * name, Getter getter, Setter setter);
            virtual void def(ScriptContext ctx);
        };
        
        class UIDocument : public kk::Document {
            DEF_CLASS(UIDocument)
        public:
            virtual kk::Float pixel(Pixel& v,kk::Float baseValue,kk::Float defaultValue);
            virtual void setPixelScale(PixelType type,kk::Float scale);
            virtual void init();
        protected:
            std::map<PixelType,kk::Float> _pixelTypeScales;
        };
        
        
        class UIElement;
        
        typedef kk::gl::vec2 (*UILayout) (UIElement * element);
        

        /**
         * 相对布局 "relative"
         */
        //extern kk::gl::vec2 UILayoutRelative(UIElement * element);
        
        /**
         * 流式布局 "flex" 左到右 上到下
         */
        //extern kk::gl::vec2 UILayoutFlex(UIElement * element);
        
        /**
         * 水平布局 "horizontal" 左到右
         */
        //extern kk::gl::vec2 UILayoutHorizontal(UIElement * element);
        
        class UIElement : public kk::gl::GLElement {
            DEF_CLASS(UIElement)
        public:
            
            virtual void begin(UITouch * touch);
            virtual void moved(UITouch * touch);
            virtual void end(UITouch * touch);
            virtual void canceled(UITouch * touch);
            virtual void isInset(UITouch * touch);
            
            virtual kk::CString layout();
            virtual void setLayout(kk::CString name);
            
            virtual kk::gl::vec2& size();
            virtual void setSize(kk::gl::vec2& v);
            
            virtual kk::gl::vec2& contentSize();
            virtual void setContentSize(kk::gl::vec2& v);
            
            virtual Pixel& width();
            virtual void setWidth(Pixel&v);
            
            virtual Pixel& height();
            virtual void setHeight(Pixel&v);
            
            virtual Pixel& minWidth();
            virtual void setMinWidth(Pixel&v);
            
            virtual Pixel& maxWidth();
            virtual void setMaxWidth(Pixel&v);
            
            virtual Pixel& minHeight();
            virtual void setMinHeight(Pixel&v);
            
            virtual Pixel& maxHeight();
            virtual void setMaxHeight(Pixel&v);
            
            virtual kk::gl::vec2& anchor();
            virtual void setAnchor(kk::gl::vec2& v);
            
            virtual Edge& margin();
            virtual void setMargin(Edge&v);
            
            virtual Edge& padding();
            virtual void setPadding(Edge&v);
            
            virtual Pixel& left();
            virtual void setLeft(Pixel&v);
            
            virtual Pixel& top();
            virtual void setTop(Pixel&v);
            
            virtual Pixel& right();
            virtual void setRight(Pixel&v);
            
            virtual Pixel& bottom();
            virtual void setBottom(Pixel&v);
            
            virtual void setLayout(UILayout layout);
            
            virtual void layoutChildren();
            
            virtual kk::Float pixel(Pixel& v,kk::Float baseValue,kk::Float defaultValue);
            
            virtual void init();
            
            static kk::StringProperty Property_layout;
            static kk::gl::Vec2Property Property_size;
            static kk::gl::Vec2Property Property_contentSize;
            static PixelProperty Property_width;
            static PixelProperty Property_height;
            static PixelProperty Property_minWidth;
            static PixelProperty Property_maxWidth;
            static PixelProperty Property_minHeight;
            static PixelProperty Property_maxHeight;
            static PixelProperty Property_left;
            static PixelProperty Property_top;
            static PixelProperty Property_right;
            static PixelProperty Property_bottom;
            static EdgeProperty Property_margin;
            static EdgeProperty Property_padding;
            
            static kk::Property *Propertys[];
            
        protected:
            virtual void onDraw(kk::gl::GLContext * ctx);
            UILayout _layout;
            kk::gl::vec2 _size;
            kk::gl::vec2 _contentSize;
            kk::gl::vec2 _anchor;
            Pixel _width;
            Pixel _height;
            Pixel _minWidth;
            Pixel _maxWidth;
            Pixel _minHeight;
            Pixel _maxHeight;
            Pixel _left;
            Pixel _right;
            Pixel _top;
            Pixel _bottom;
            Edge _padding;
            Edge _margin;
        };
        
    }
    
}

#endif /* kk_ui_hpp */
