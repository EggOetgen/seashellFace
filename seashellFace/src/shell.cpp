//
//  shell.cpp
//  seashellOFX
//
//  Created by Edmund Oetgen on 18/07/2017.
//
//

#include "shell.hpp"

void shell::generate(int n, int m, int D, float turns, float alpha, float beta, float A, float mu, float omega, float phi, float a, float b, float L, float P, float W1, float W2, int N)
{
   
    // adjust resolution of mesh for number of shell turns
    n = (int) ( n * turns / 10.0);
    
    spiral.clear();
    shell.clear();
    
    spiral.resize(n);
    shell.resize(n);
    
    for (int i = 0; i < n; i++){
        shell[i].resize(m);
    }
    
    // Get vertices for the shell
    for (int i = 0; i < n; i++)
    {
        // Generate main spiral
        float theta = ofMap(i, 0, n, 0, turns);
        float rad = exp( theta * cos(alpha) / sin(alpha) );
        
        float x =  A * rad * sin(beta) * cos(theta) * D;
        float y =  A * rad * sin(beta) * sin(theta);
        float z = -A * rad * cos(beta);
        
        spiral[i] = ofPoint(x, y, z);
        
        // Generate ellipse around each point of spiral
        for (int j = 0; j < m; j++)
        {
            float s = ofMap(j, 0, m, 0, TWO_PI);
            float r2 = pow( pow(cos(s)/a,2) + pow(sin(s)/b,2), -0.5 );
            
            // add surface manipulations
            float surfrad = 0;
            if (W1==0 || W2==0 || N==0) surfrad = 0;
            else {
                float lt = (TWO_PI / N) * ( N*theta / TWO_PI - int(N*theta / TWO_PI) );
                surfrad = L * exp( -( pow(2*(s-P)/W1, 2) + pow(2*lt/W2, 2) ) );
            }
            r2 += surfrad;
            
            x = cos(s + phi) * cos(theta + omega) * r2 * rad * D;   // here  rad - 1 closes the opening of the curve at the origin
            y = cos(s + phi) * sin(theta + omega) * r2 * rad;
            z = sin(s + phi)                      * r2 * rad;
            
            // adjust orientation of the
            x -= sin(mu) * sin(s + phi) * sin(theta + omega) * r2;
            y += sin(mu) * sin(s + phi) * cos(theta + omega) * r2;
            z *= cos(mu);
            
            shell[i][j] = spiral[i] + ofPoint(x, y, z);
        }
    }
}

void shell::generateMesh(int n, int m, float turns)
{
    
    // adjust resolution of mesh for number of shell turns
    
    n = (int) (n * turns / 20.0);
    
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int pos = i + n * j;
            vertices.push_back(shell[i][j]);
            
        }
    }
    
    shellMesh.clear();
    for (int i = 0; i < vertices.size(); i++) {
        shellMesh.addVertex(vertices[i]);
          shellMesh.addColor(ofFloatColor(ofMap(i, 0.f, vertices.size(),0.7f,0.9f),0.788,0.761));
      //  shellMesh.addColor(ofFloatColor(0.894,0.788,0.761));
    }
    
    //the following thanks to jake sparrow hunter
    for (int i = m ; i < vertices.size(); i++) {
        if (i < vertices.size() && i != m){
            //TRI1
            //this point
            shellMesh.addIndex(i);
            //to previous point
            shellMesh.addIndex(i-1);
            //to this point on the previous ring
            shellMesh.addIndex(i-m);
            
            //TRI2
            //the previous point
            shellMesh.addIndex(i-1);
            //to the previous point on the previous ring
            shellMesh.addIndex(i-m-1);
            //to one after that
            shellMesh.addIndex(i-m);
        }
    }
//    shellNode.getMesh().clear();
//    for (int i = 0; i < vertices.size(); i++) {
//        shellNode.getMesh().addVertex(vertices[i]);
//        shellNode.getMesh().addColor(ofFloatColor(ofMap(i, 0.f, vertices.size(),0.7f,0.9f),0.788,0.761));
//        //  shellMesh.addColor(ofFloatColor(0.894,0.788,0.761));
//    }
//    
//    //the following thanks to jake sparrow hunter
//    for (int i = m ; i < vertices.size(); i++) {
//        if (i < vertices.size() && i != m){
//            //TRI1
//            //this point
//            shellNode.getMesh().addIndex(i);
//            //to previous point
//            shellNode.getMesh().addIndex(i-1);
//            //to this point on the previous ring
//            shellNode.getMesh().addIndex(i-m);
//            
//            //TRI2
//            //the previous point
//            shellNode.getMesh().addIndex(i-1);
//            //to the previous point on the previous ring
//            shellNode.getMesh().addIndex(i-m-1);
//            //to one after that
//            shellNode.getMesh().addIndex(i-m);
//        }
//    }
}

void shell::draw(int m){
    

 
  //  shellMesh.drawWireframe();
    
    
    ofVec3f axis;
    float angle;
    curRot.getRotate(angle, axis);
    centroid = shellMesh.getCentroid();
    centroid.rotate(angle, axis);
    test.setPosition(centroid);
//    ofDrawBox(test.getPosition(), 20);
    //test.draw();
    
    ofPushMatrix();
   

   
    ofRotate(angle, axis.x, axis.y, axis.z);
    shellMesh.draw();
//    float r = 5;
// //   ofSetColor(120,20);
//    for (int i = 0; i < shell.size(); i+=4){
//        for(int j = 0; j < shell[i].size(); j+=4){
//            
//            ofDrawSphere(shell[i][j], r);
//           // r *= 1.0000001;
//        }
//    }

           ofPopMatrix();

    //    ofPushMatrix();
//    ofTranslate(50,0,0);

//    float r = 5;
//    for (int i = shell.size()/4; i < shell.size(); i+=4){
//        for(int j = 0; j < shell[i].size(); j+=4){
//            
//            ofDrawSphere(shell[i][j], r);
//            r *= 1.0000001;
//        }
//    }
//    ofPopMatrix();
    
  }

void shell::updateMesh(int n, int m, float turns){
    
    n = (int) (n * turns / 20.0);
    vertices.clear();
    float distSqr;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int pos = i + n * j;
            distSqr = shell[i][j].squareDistance(centroid);
            if (distSqr > largestDistanceSquared) largestDistanceSquared = distSqr;
            vertices.push_back(shell[i][j]);
            
            
        }
    }
    
    for (int i = 0; i < vertices.size(); i++) {
        shellMesh.setVertex(i, vertices[i]);
    }
    setNormals(shellMesh);
    largestDistance = sqrt(largestDistanceSquared);
    }


//MODIFIED FROM 'MASTERING OPENFRAMEWORKS' BY Denis Perevalov
void shell::setNormals( ofMesh &mesh )
{
    //The number of the vertices
    int nV = mesh.getNumVertices();
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    vector<glm::tvec3< float, glm::precision::packed_highp>> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).cross( v3 - v1 ) ).normalize();
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        ofPoint p;
        p.x = norm[i].x;
        p.y = norm[i].y;
        p.z = norm[i].z;
        p.normalize();
        
        norm[i].x = p.x;
        norm[i].y = p.y;
        norm[i].z = p.z;
    }

    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}


//taken from https://forum.openframeworks.cc/t/up-down-left-right-rotation-problem-please-help/8328/2
void shell::move(int x, int y, ofVec2f lastMouse){
  
    ofVec2f mouse(x/10,y/10);
    ofQuaternion yRot(x-lastMouse.x, ofVec3f(0,1,0));
    ofQuaternion xRot(y-lastMouse.y, ofVec3f(-1,0,0));
    curRot *= yRot*xRot;
  //  lastMouse = mouse;

}