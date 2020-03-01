#include "integrators/whitted.h"

vec3 Whitted::Li(std::shared_ptr<Ray> ray, std::shared_ptr<Sampler> sampler, Scene &scene) {
    vec3 L(0);
    HitInfo p;

    // Find closest ray interaction or return background
    if (!scene.Intersect(ray, p)) {
        // Background color
        L = vec3(0, 0.2, 0.3);
        return L;
    }

    // TODO Add emitted light of object

    // Lighting params
    float ambient = 0.2;
    float diffuseStrength = 1;
    float specularStrength = 1;

    // Add contribution of each light source
    for (int i = 0; i < scene.lights.size(); i++) {
        // Direction to light source
        vec3 wi;

        // Probability of sampling from a specific light
        float pdf = 1 / float(scene.lights.size());

        // Attenuated light
        vec3 Li = scene.lights[i]->SampleLi(p, wi);

        // TODO Implement BSDF

        // Apply diffuse lighting
        float diffuse = glm::dot(wi, p.normal) * diffuseStrength;

        // Apply specular reflection
        int shininess = 16;
        vec3 halfwayVector = glm::normalize(wi + -ray->direction());
        float specularAngle = std::max(glm::dot(p.normal, halfwayVector), 0.0f);
        float specular = std::pow(specularAngle, shininess) * specularStrength;

        L += Li * std::min((ambient + diffuse + specular), 1.0f) * pdf;
    }

    // If shadow ray hits nothing
    vec3 objectColor = vec3(0.8, 0.2, 0.2);
    L *= objectColor;

    // TODO If shadow ray hits object, do recursion

    return L;
}
