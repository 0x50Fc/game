

var root = new Element(document);

document.rootElement = root;

(function(p){
 
 var v = new GMSceneElement(document);
 p.append(v);
 
 (function(p){

  var v = new GMTextureElement(document);
  
  v.name = "m1"
  v.path = "/m1.png"
  
  p.append(v);
  
  })(v);
 
 (function(p){
  
  var v = new GLImageElement(document);
  
  v.name = "m1"
  v.size = [1,1];
  v.anchor = [0.5,0.5];
  
  p.append(v);
  
  })(v);
 
 })(root);


