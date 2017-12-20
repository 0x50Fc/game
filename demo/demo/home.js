

var root = new Element(document);

document.rootElement = root;

(function(p){
 
 var v = new GMSceneElement(document);
 p.append(v);
 
 (function(p){

  var v = new GMTextureElement(document);
  
  v.name = "tmw_desert_spacing.png"
  v.path = "/tmw_desert_spacing.png"
  
  p.append(v);
  
  })(v);
 
 (function(p){
  
  var v = new GMTextureElement(document);
  
  v.name = "pay.png"
  v.path = "/pay.png"
  
  p.append(v);
  
  })(v);
 
 (function(p){
  
  var v = new GLImageElement(document);
  
  v.name = "pay.png"
  v.anchor = [0,0];
  v.scale = [0.5,0.5,1];
  //p.append(v);
  
  })(v);

 
 (function(p){
  
  var v = new GLTMXElement(document);
  
  v.scale = [1.5,1.5,1];
  v.path = "/desert.tmx"
  p.append(v);
  
  })(v);
 
 (function(p){
  
  var v = new GLTextElement(document);
  
  v.text = "hello world";
  v.anchor = [0,0];
  v.position = [200,200,1];
  v.fontSize = 16;
  
  p.append(v);
  
  })(v);
 
 })(root);


