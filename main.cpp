#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Object3D.h"
#include "Polygon.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"

struct Scene {
    // Camera
    Vec3 lookFrom, lookAt, lookUp;
    double fov{};

    // Lights/Background
    Vec3 dirToLight, lightColor, ambientLight, backgroundColor;

    // Objects
    std::vector<std::unique_ptr<Object3D>> objects;
};

Scene getPgm5Scene1() {
    Scene s;
    
    s.lookFrom = Vec3(0,0,1);
    s.lookAt = Vec3(0,0,0);
    s.lookUp = Vec3(0,1,0);
    s.fov = 90.0;

    s.dirToLight = Vec3(0,1,0).normalize();
    s.lightColor = Vec3(1,1,1);
    s.ambientLight = Vec3(0,0,0);
    s.backgroundColor = Vec3(.2,.2,.2);

    // PURPLE SPHERE
    Material purple_mat(.7,.2,.1,Vec3(1,0,1),Vec3(1,1,1),16,0);
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0,0,0), .4, purple_mat));
    return s;
}

Scene getPgm5Scene2() {
    Scene s;
    
    s.lookFrom = Vec3(0,-0.3,1);
    s.lookAt = Vec3(0,0,0);
    s.lookUp = Vec3(0,1,0);
    s.fov = 90.0;

    s.dirToLight = Vec3(1,1,1).normalize();
    s.lightColor = Vec3(1,1,1);
    s.ambientLight = Vec3(.1,.1,.1);
    s.backgroundColor = Vec3(.2,.2,.2);

    // WHITE SPHERE
    Material white_mat(.8,.1,.3,Vec3(1,1,1),Vec3(1,1,1),4.1,0.2);

    // RED SPHERE
    Material red_mat(.6,.3,.1,Vec3(1,0,0),Vec3(1,1,1),32.6,0.4);

    // GREEN SPHERE
    Material green_mat(.7,.2,.1,Vec3(0,1,0),Vec3(.5,1,.5),64.4,0.6);

    // BLUE SPHERE
    Material blue_mat(.9,0,.1,Vec3(0,0,1),Vec3(1,1,1),16.2,0.1);

    s.objects.push_back(std::make_unique<Sphere>(Vec3(.45,0,-.15), .15, white_mat));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0,0,-.1), .2, red_mat));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-.6,0,0), .3, green_mat));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0,-10000.5,0), 10000.0, blue_mat));

    return s;
}

Scene getPgm5Scene3() {
    Scene s;

    s.lookFrom = Vec3(0,0,1);
    s.lookAt = Vec3(0,0,0);
    s.lookUp = Vec3(0,1,0);
    s.fov = 90.0;

    s.dirToLight = Vec3(1,1,1).normalize();
    s.lightColor = Vec3(1,1,1);
    s.ambientLight = Vec3(.1,.1,.1);
    s.backgroundColor = Vec3(.2,.2,.2);

    // Materials
    Material snow_mat(0.85, 0.1, 0.2, Vec3(1.0, 1.0, 1.0), Vec3(1.0, 1.0, 1.0), 4.0,0);
    Material coal_mat(0.1, 0.05, 0.05, Vec3(0.1, 0.1, 0.1), Vec3(0.5, 0.5, 0.5), 2.0,0);
    Material floor_mat(0.9, 0.0, 0.1, Vec3(0.9, 0.9, 1.0), Vec3(1.0, 1.0, 1.0), 16.0,0.23);

    // Floor
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, -10000.5, 0), 10000.0, floor_mat));

    // Snowman lambda
    auto addSnowman = [&](const Vec3 &pos, const double scale) {
        s.objects.push_back(std::make_unique<Sphere>(Vec3(pos.x, pos.y, pos.z), 0.3 * scale, snow_mat));
        s.objects.push_back(std::make_unique<Sphere>(Vec3(pos.x, pos.y + 0.45 * scale, pos.z), 0.2 * scale, snow_mat));
        s.objects.push_back(std::make_unique<Sphere>(Vec3(pos.x, pos.y + 0.75 * scale, pos.z), 0.15 * scale, snow_mat));
        // Eyes
        s.objects.push_back(std::make_unique<Sphere>(Vec3(pos.x - 0.05 * scale, pos.y + 0.80 * scale, pos.z + 0.13 * scale), 0.02 * scale, coal_mat));
        s.objects.push_back(std::make_unique<Sphere>(Vec3(pos.x + 0.05 * scale, pos.y + 0.80 * scale, pos.z + 0.13 * scale), 0.02 * scale, coal_mat));
    };

    addSnowman(Vec3(0.0, -0.2, -0.5), 1.0);    // Center
    addSnowman(Vec3(-0.7, -0.3, -0.2), 0.8);   // Left foreground
    addSnowman(Vec3(0.8, -0.4, -0.8), 0.6);    // Right midground
    addSnowman(Vec3(-1.2, -0.3, -1.5), 1.2);   // Far left (big)
    addSnowman(Vec3(1.5, -0.4, -2.0), 0.9);    // Far right

    return s;
}

Scene getPgm6Scene1() {
    Scene s;

    s.lookAt = Vec3(0,0,0);
    s.lookFrom = Vec3(0,0,1);
    s.lookUp = Vec3(0,1,0);
    s.fov = 90.0;

    s.dirToLight = Vec3(0,1,0);
    s.lightColor = Vec3(1,1,1);
    s.ambientLight = Vec3(0,0,0);
    s.backgroundColor = Vec3(0.2,0.2,0.2);

    // REFLECTIVE SPHERE
    Material reflSphere(0.0,0.1,0.1,Vec3(.75,.75,.75),Vec3(1,1,1),10,0.9);
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0,0.3,-1.0), 0.25, reflSphere));

    // BLUE TRIANGLE
    Material blueTri(.9,1.0,0.1,Vec3(0,0,1),Vec3(1,1,1),4.0,0);
    std::vector<Vec3> vertices;
    vertices.emplace_back(0,-.7,-.5);
    vertices.emplace_back(1,.4,-1);
    vertices.emplace_back(0,-.7,-1.5);
    s.objects.push_back(std::make_unique<Triangle>(vertices,blueTri));
    vertices.clear();

    // YELLOW TRIANGLE
    Material yellowTri(.9,1.0,.1,Vec3(1,1,0),Vec3(1,1,1),4.0,0);
    vertices.emplace_back(0,-.7,-.5);
    vertices.emplace_back(0,-.7,-1.5);
    vertices.emplace_back(-1,.4,-1);
    s.objects.push_back(std::make_unique<Triangle>(vertices,yellowTri));

    return s;
}

Scene getPgm6Scene2() {
    Scene s;

    s.lookAt = Vec3(0,0,0);
    s.lookFrom = Vec3(0,0,1);
    s.lookUp = Vec3(0,1,0);
    s.fov = 90.0;

    s.dirToLight = Vec3(1,0,0);
    s.lightColor = Vec3(1,1,1);
    s.ambientLight = Vec3(0.1,0.1,0.1);
    s.backgroundColor = Vec3(0.2,0.2,0.2);

    // WHITE SPHERE
    Material whiteSphere(0.8,0.1,0.3,Vec3(1,1,1),Vec3(1,1,1),4,0.0);
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.5,0,-.15), 0.05, whiteSphere));

    // RED SPHERE
    Material redSphere(0.8,0.8,0.1,Vec3(1,0,0),Vec3(0.5,1,0.5),32.0,0.0);
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.3,0,-.1), 0.08, redSphere));

    // RED SPHERE
    Material greenSphere(0.7,0.5,0.1,Vec3(0,1,0),Vec3(0.5,1,0.5),64.0,0.0);
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-.6,0,0), 0.3, greenSphere));

    // REFLECTIVE SPHERE
    Material reflSphere(0,0.1,0.1,Vec3(.75,.75,.75),Vec3(1,1,1),10,0.9);
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.1,-.55,.25), 0.3, reflSphere));

    // BLUE TRIANGLE
    Material blueTri(.9,.9,0.1,Vec3(0,0,1),Vec3(1,1,1),32,0);
    std::vector<Vec3> vertices;
    vertices.emplace_back(0.3,-.3,-.4);
    vertices.emplace_back(0,.3,-.1);
    vertices.emplace_back(-0.3,-.3,.2);
    s.objects.push_back(std::make_unique<Triangle>(vertices,blueTri));
    vertices.clear();

    // YELLOW TRIANGLE
    Material yellowTri(.9,.5,.1,Vec3(1,1,0),Vec3(1,1,1),4.0,0);
    vertices.emplace_back(-.2,.1,.1);
    vertices.emplace_back(-.2,-.5,.2);
    vertices.emplace_back(-.2,0.1,-.3);
    s.objects.push_back(std::make_unique<Triangle>(vertices,yellowTri));

    return s;
}

Scene getFlapjackScene() {
    Scene s;

    // Camera setup - Shifted to the left (-2.5 on X) and pulled back for a 3/4 profile shot
    s.lookFrom = Vec3(-.5, 3.0, 5.5);
    s.lookAt = Vec3(0, 0.8, 0);
    s.lookUp = Vec3(0, 1, 0);
    s.fov = 50.0;

    // Strong directional light to create dramatic shadows
    s.dirToLight = Vec3(1, 2, 1).normalize();
    s.lightColor = Vec3(1, 1, 1);

    // Pumped up ambient light to reveal the coat colors
    s.ambientLight = Vec3(3.0, 3.0, 3.0);
    s.backgroundColor = Vec3(0.5, 0.7, 0.9); // Sky blue to make the black coat pop

    // --- MATERIALS ---
    // Deep black coat (Low diffuse, slight specular shine for a healthy coat)
    Material blackFur(0.8, 0.2, 0.1, Vec3(0.08, 0.08, 0.08), Vec3(0.2, 0.2, 0.2), 16.0, 0.0);
    // Rich mahogany/tan markings
    Material tanFur(0.8, 0.2, 0.1, Vec3(0.7, 0.4, 0.1), Vec3(0.2, 0.2, 0.2), 16.0, 0.0);
    // Wet black look for nose and eyes (High specular)
    Material wetBlack(0.1, 0.9, 0.1, Vec3(0.02, 0.02, 0.02), Vec3(1, 1, 1), 128.0, 0.0);
    // Reflective Floor
    Material reflFloor(0.5, 0.3, 0.1, Vec3(0.8, 0.8, 0.8), Vec3(1, 1, 1), 64.0, 0.4);

    // --- GEOMETRY ---

    // 1. The Reflective Floor
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, -10000.0, 0), 10000.0, reflFloor));

    // 2. Body & Tail
    // Overlapping black spheres to create an elongated torso
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 0.8, -0.8), 0.7, blackFur)); // Back half
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 0.9, -0.2), 0.75, blackFur)); // Front chest
    // Tail sweeping out the back
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 0.9, -1.5), 0.25, blackFur));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 1.0, -1.8), 0.15, blackFur));

    // 3. Chest Fluff
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 0.6, 0.4), 0.4, tanFur));

    // 4. Head & Face
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 1.4, 0.2), 0.55, blackFur)); // Skull
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 1.2, 0.65), 0.25, tanFur));  // Muzzle

    // The iconic tan eyebrows (pips) and cheeks
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-0.2, 1.7, 0.62), 0.06, tanFur)); // Left pip
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.2, 1.7, 0.62), 0.06, tanFur));  // Right pip
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-0.35, 1.15, 0.5), 0.15, tanFur)); // Left cheek
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.35, 1.15, 0.5), 0.15, tanFur));  // Right cheek

    // Nose & Eyes
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0, 1.3, 0.88), 0.08, wetBlack));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-0.2, 1.5, 0.65), 0.08, wetBlack));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.2, 1.5, 0.65), 0.08, wetBlack));

    // 5. The Floppy Ears (Lifted higher onto the crown of the head)
    std::vector<Vec3> earVerts;

    // Left Ear Main Flap
    earVerts.emplace_back(-0.45, 1.8, 0.1);  // Raised Y and pushed X slightly out
    earVerts.emplace_back(-1.1, 0.7, 0.3);   // Raised drop point
    earVerts.emplace_back(-0.5, 0.9, 0.6);   // Raised cheek contact
    s.objects.push_back(std::make_unique<Triangle>(earVerts, blackFur));
    earVerts.clear();

    // Left Ear Inner Fold
    earVerts.emplace_back(-0.45, 1.8, 0.1);
    earVerts.emplace_back(-0.5, 0.9, 0.6);
    earVerts.emplace_back(-0.2, 1.1, 0.1);
    s.objects.push_back(std::make_unique<Triangle>(earVerts, blackFur));
    earVerts.clear();

    // Right Ear Main Flap (Mirrored)
    earVerts.emplace_back(0.45, 1.8, 0.1);
    earVerts.emplace_back(0.5, 0.9, 0.6);
    earVerts.emplace_back(1.1, 0.7, 0.3);
    s.objects.push_back(std::make_unique<Triangle>(earVerts, blackFur));
    earVerts.clear();

    // Right Ear Inner Fold
    earVerts.emplace_back(0.45, 1.8, 0.1);
    earVerts.emplace_back(0.2, 1.1, 0.1);
    earVerts.emplace_back(0.5, 0.9, 0.6);
    s.objects.push_back(std::make_unique<Triangle>(earVerts, blackFur));
    earVerts.clear();

    // 6. Legs & Paws
    // Front Legs (Tan)
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-0.3, 0.2, 0.6), 0.2, tanFur));  // Left arm
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-0.3, 0.1, 0.8), 0.15, tanFur)); // Left paw
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.3, 0.2, 0.6), 0.2, tanFur));   // Right arm
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.3, 0.1, 0.8), 0.15, tanFur));  // Right paw

    // Back Paws (Tan, tucked slightly under)
    s.objects.push_back(std::make_unique<Sphere>(Vec3(-0.4, 0.15, -0.6), 0.15, tanFur));
    s.objects.push_back(std::make_unique<Sphere>(Vec3(0.4, 0.15, -0.6), 0.15, tanFur));

    return s;
}

Vec3 rayColor(const Ray& ray, const Scene& scene, const int depth) {
    if (depth <= 0) return {0,0,0}; // Base case

    double closest_t = 1e30;
    Object3D* hit_obj = nullptr;

    for (const auto& objPtr : scene.objects) {
        double t = objPtr->hit(ray);
        if (t > 0.0 && t < closest_t) {
            closest_t = t;
            hit_obj = objPtr.get();
        }
    }
    if (hit_obj != nullptr) {
        Vec3 p = ray.at(closest_t); // intersection point
        Vec3 n = hit_obj->getNormal(p); // normal vector

        // SHADOW
        int shadowMult = 1;
        Vec3 safeP = p + (0.0001 * n);
        Ray shadowRay(safeP,scene.dirToLight.normalize());
        for (const auto& objPtr : scene.objects) {
            double t = objPtr->hit(shadowRay);
            if (t > 0.0) {
                shadowMult = 0;
                break;
            }
        }

        // DIFFUSE
        Material& m = hit_obj->mat;

        Vec3 viewDir = (scene.lookFrom - p).normalize(); // view vector
        Vec3 incidentDir = -scene.dirToLight; // incident vector
        Vec3 r = (incidentDir - n * 2.0 * incidentDir.dot(n)).normalize(); // reflection vector

        // PHONG SHADING
        Vec3 ambient = m.k_a * scene.ambientLight * m.o_d;
        Vec3 diffuse = m.k_d * scene.lightColor * m.o_d * std::max(0.0,n.dot(scene.dirToLight));
        Vec3 specular = m.k_s * scene.lightColor * m.o_s * std::pow(std::max(0.0,viewDir.dot(r)),m.k_gls);

        Vec3 color = ambient + diffuse*shadowMult + specular*shadowMult;

        // REFLECTION LOOP
        if (m.refl > 0.0) {
            const Vec3 mirrorDir = (ray.dir - 2.0 * n * ray.dir.dot(n)).normalize();
            const Ray reflRay(safeP, mirrorDir);
            const Vec3 reflectedColor = rayColor(reflRay, scene, depth - 1);
            color = color + (reflectedColor * hit_obj->mat.refl);
        }
        return color;
    }
    return scene.backgroundColor;
}

int main() {
    // Wrap everything in an infinite loop
    while (true) {
        // SCENE SELECTION UI
        std::cout << "\n========================================\n"
                  << "Select a scene to render:\n"
                  << "0. Exit Program\n"
                  << "1. Pgm5 Scene 1 (Purple Sphere)\n"
                  << "2. Pgm5 Scene 2 (4 Colored Spheres)\n"
                  << "3. Pgm5 Scene 3 (Snowmen)\n"
                  << "4. Pgm6 Scene 1 (Reflective Sphere & Triangles)\n"
                  << "5. Pgm6 Scene 2 (More Spheres & Triangles)\n"
                  << "6. Flapjack Scene (Custom)\n"
                  << "Enter choice (e.g., '6', '6 -png', or '6 -o render.png'): ";

        // 1. READ THE WHOLE LINE
        std::string input;
        std::getline(std::cin, input);

        // If the user just presses Enter without typing, ask again
        if (input.empty()) {
            continue;
        }

        // 2. PARSE THE INPUT
        std::stringstream ss(input);
        std::string token;
        
        ss >> token;

        // Check if the user wants to exit
        if (token == "0" || token == "exit" || token == "quit") {
            break;
        }

        int choice = 1;
        try { choice = std::stoi(token); } 
        catch (...) { std::cout << "Invalid choice. Defaulting to Scene 1.\n"; }

        bool usePng = false;
        std::string customFilename = "";

        // Loop through the rest of the words in the input
        while (ss >> token) {
            if (token == "-png") {
                usePng = true;
            } else if (token == "-o") {
                ss >> customFilename;
            }
        }

        Scene scene;
        std::string defaultBaseFilename;

        // 3. MAP SCENE
        switch (choice) {
            case 1: scene = getPgm5Scene1(); defaultBaseFilename = "Pgm5Scene1_Updated"; break;
            case 2: scene = getPgm5Scene2(); defaultBaseFilename = "Pgm5Scene2_Updated"; break;
            case 3: scene = getPgm5Scene3(); defaultBaseFilename = "Pgm5Scene3_Updated"; break;
            case 4: scene = getPgm6Scene1(); defaultBaseFilename = "Pgm6Scene1_Updated"; break;
            case 5: scene = getPgm6Scene2(); defaultBaseFilename = "Pgm6Scene2_Updated"; break;
            case 6: scene = getFlapjackScene(); defaultBaseFilename = "FlapjackScene_Updated"; break;
            default:
                scene = getPgm5Scene1();
                defaultBaseFilename = "Pgm5Scene1_Updated";
                break;
        }

        // 4. RESOLVE FINAL FILENAME
        std::string filename;
        if (!customFilename.empty()) {
            filename = customFilename;
            if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".png") {
                usePng = true;
            } else if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".ppm") {
                usePng = false;
            }
        } else {
            filename = defaultBaseFilename + (usePng ? ".png" : ".ppm");
        }

        std::cout << "\nRendering " << filename << "...\n";

        // IMAGE VARIABLES
        constexpr int image_width = 1920;
        constexpr int image_height = 1080;
        auto AR = static_cast<double>(image_width) / image_height;

        // CAMERA COORDINATES
        auto w = (scene.lookFrom - scene.lookAt).normalize();
        auto u = scene.lookUp.cross(w).normalize();
        auto v = w.cross(u);

        double radFOV = scene.fov * M_PI / 180.0;
        auto d = (scene.lookAt - scene.lookFrom).length();
        double windowHeight = 2.0 * d * std::tan(radFOV / 2.0);
        double windowWidth = windowHeight * AR;

        double pixelX = windowWidth / image_width;
        double pixelY = windowHeight / image_height;

        // CREATE BUFFER
        std::vector<unsigned char> image_data(image_width * image_height * 3);

        // PIXEL LOOP
        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                int rayDepth = 4;
                const double xPrime = -windowWidth / 2 + pixelX / 2 + i * pixelX;
                const double yPrime = windowHeight / 2 - pixelY / 2 - j * pixelY;

                Vec3 pixelPos = scene.lookAt + (u * xPrime) + (v * yPrime);
                auto ray = Ray(scene.lookFrom, (pixelPos - scene.lookFrom).normalize());

                Vec3 color = rayColor(ray, scene, rayDepth);

                int red = std::min(255, static_cast<int>(color.x * 255));
                int green = std::min(255, static_cast<int>(color.y * 255));
                int blue = std::min(255, static_cast<int>(color.z * 255));

                int index = (j * image_width + i) * 3;
                image_data[index + 0] = red;
                image_data[index + 1] = green;
                image_data[index + 2] = blue;
            }
        }

        // 5. OUTPUT BRANCH
        if (usePng) {
            stbi_write_png(filename.c_str(), image_width, image_height, 3, image_data.data(), image_width * 3);
        } else {
            std::ofstream out_file(filename);
            out_file << "P3\n" << image_width << " " << image_height << "\n255\n";
            for (size_t i = 0; i < image_data.size(); i += 3) {
                out_file << static_cast<int>(image_data[i]) << " "
                         << static_cast<int>(image_data[i + 1]) << " "
                         << static_cast<int>(image_data[i + 2]) << "\n";
            }
            out_file.close();
        }

        std::cout << "Render complete!\n";
    } // End of while loop

    return 0;
}