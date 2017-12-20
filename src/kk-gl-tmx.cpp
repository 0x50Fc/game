//
//  kk-gl-tmx.cpp
//  KKGame
//
//  Created by hailong11 on 2017/12/18.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//


#include "kk-config.h"
#include "kk-gl-tmx.h"

#include "tmx.h"

#ifdef __APPLE__

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#endif

#include <strstream>

namespace kk {

    namespace gl {
        
        
        GLTMXElement::~GLTMXElement() {
            if(_map) {
                tmx_map_free(_map);
            }
        }
        
        CString GLTMXElement::path() {
            return _path.c_str();
        }
        
        void GLTMXElement::setPath(CString path) {
            _path = path;
            if(_map) {
                tmx_map_free(_map);
                _map = NULL;
            }
        }
        
        void GLTMXElement::loadMap() {
            
            if(_map == NULL) {
                Document * doc = document();
                if(doc) {
                    Application * app =doc->app();
                    if(app && app->has(path())) {
                        std::strstream s;
                        s << app->basePath() << path() << std::ends;
                        _map = tmx_load(s.str());
                        if(_map == NULL) {
                            kk::Log("TMX: %s",tmx_strerr());
                        }
                    }
                }
            }
            
        }
        
        
        static unsigned int gid_clear_flags(unsigned int gid) {
            return gid & TMX_FLIP_BITS_REMOVAL;
        }
        
        static void draw_layer(GLTMXElement *e, GLContext * ctx,tmx_map *map, tmx_layer *layer) {
            unsigned long i, j;
            unsigned int gid;
            float op;
            tmx_tileset *ts;
            tmx_image *im;
            vec4 srcrect(0), dstrect(0);
            GLTexture * texture;
            op = layer->opacity;
            for (i=0; i<map->height; i++) {
                for (j=0; j<map->width; j++) {
                    gid = gid_clear_flags(layer->content.gids[(i*map->width)+j]);
                    if (map->tiles[gid] != NULL) {
                        ts = map->tiles[gid]->tileset;
                        im = map->tiles[gid]->image;
                        srcrect.x = map->tiles[gid]->ul_x;
                        srcrect.y = map->tiles[gid]->ul_y;
                        srcrect.z = dstrect.z = ts->tile_width;
                        srcrect.w = dstrect.w = ts->tile_height;
                        dstrect.x = j*ts->tile_width;  dstrect.y = i*ts->tile_height;
                        if (im) {
                            texture = e->getTexture(im->source);
                        }
                        else {
                            texture = e->getTexture(ts->image->source);
                        }
                        ctx->drawTexture(texture, dstrect, srcrect);
                    }
                }
            }
        }
        
        static void draw_image_layer(GLTMXElement *e,GLContext * ctx,tmx_image *img) {
            GLTexture * texture = e->getTexture(img->source);
            ctx->drawTexture(texture, vec4(0,0,img->width,img->height), vec4(0,0,img->width,img->height));
        }
        
        static void draw_all_layers(GLTMXElement *e,GLContext * ctx,tmx_map *map, tmx_layer *layers) {
            while (layers) {
                if (layers->visible) {
                    if (layers->type == L_GROUP) {
                        draw_all_layers(e,ctx,map, layers->content.group_head);
                    } else if (layers->type == L_OBJGR) {
                        //draw_objects(layers->content.objgr);
                    } else if (layers->type == L_IMAGE) {
                        draw_image_layer(e,ctx,layers->content.image);
                    } else if (layers->type == L_LAYER) {
                        draw_layer(e,ctx,map, layers);
                    }
                }
                layers = layers->next;
            }
        }
        
        void GLTMXElement::onDraw(GLContext * ctx) {
           
            loadMap();
            
            if(_map) {
                draw_all_layers(this,ctx,_map,_map->ly_head);
            }
        }
        
        void GLTMXElement::init() {
            GLElement::init();
            _map = NULL;
        }
        
        kk::StringProperty GLTMXElement::Property_path(&kk::named::path,(kk::StringProperty::Getter)&GLTMXElement::path,(kk::StringProperty::Setter)&GLTMXElement::setPath);

        kk::Property * GLTMXElement::Propertys[] = {
            &GLTMXElement::Property_path,
            NULL
        };
        
        IMP_CLASS(GLTMXElement, kk::gl::GLElement, GLTMXElement::Propertys, NULL)
        
        
    }
    
}

