#define COUNT 1000
#define PI 3.14159265
#define MaxError 0.0001
#define MaxDistance 1000.0

cbuffer Constant
{
	float4 viewPoint;
	float4 lightColor;
	float4 upDirection;
	float4 lightPosition;
	float4 rightDirection;
	float4 forwardDirection;

	float4 colors[COUNT];
	float4 positions[COUNT];
	float4 triangles[COUNT];
};

float3 InterpolateVector(float3 t, float3 v0, float3 v1, float3 v2)
{
	return v0*t.x+v1*t.y+v2*t.z;
}

float4 IntersectTriangle(float3 p1, float3 p2, float3 p3, float3 o, float3 d)
{
	float4 noIntersection=float4(0, 0, 0, MaxDistance); 
	/*
		solve plane equation Ax+By+Cz+D=0
		which intersects with ray p(t)=o+d*t
		solve the t as the distance: 

			t=-(dot(n, o)+w)/dot(n, d),
			where w=-dot(n, p1)

		if t<MaxError: there is no intersection

		calculate area of triangle p1 p2 p3 as S
		calculate area of triangle p p2 p3 as S1
		calculate area of triangle p1 p p3 as S2
		calculate area of triangle p1 p2 p as S3
		if S1+S2+S3>S+MaxError: there is no intersection

		Otherwsie: return  float4(S1/S, S2/S, S3/S, t);
	*/
    float3 PlaneNormal = cross((p2 - p1), (p3 - p1));
    float3 CameraVectorD = -(dot(PlaneNormal, p1));
	
    float t = -(dot(PlaneNormal, o) + CameraVectorD) / (dot(PlaneNormal, d));
	if(t<MaxError)
        return noIntersection;
    float3 p = o + t * d;
	
    float S = (0.5) * length(cross(p2 - p1, p3 - p1));
    float S1 = (0.5) * length(cross(p2 - p, p3 - p));
    float S2 = (0.5) * length(cross(p - p1, p3 - p1));
    float S3 = (0.5) * length(cross(p2 - p1, p - p1));
    if (S1 + S2 + S3 > S + MaxError)
    {
        return noIntersection;
    }
    else
    {
        return float4(S1 / S, S2 / S, S3 / S, t);
    }
}

// Call this function to intersect the ray with the i th traingle in the scene
float4 IntersectTriangle(uint i, float3 origin, float3 direction)
{
	uint i0=uint(triangles[i].x), i1=uint(triangles[i].y), i2=uint(triangles[i].z);
	float3 p0=positions[i0].xyz, p1=positions[i1].xyz, p2=positions[i2].xyz;
	return IntersectTriangle(p0, p1, p2, origin, direction);
}

 // Calculate the nearest intersection between ray and traingles
float4 IntersectTriangles(float3 origin, float3 direction)
{
	float4 nearestIntersection=float4(0, 0, 0, MaxDistance);
	// Reminder: triangles[0].w specifies how many triangles in total
	/*
		Given a ray with origin and direction as input
		find the nearest intersection among all of the traingles 
		in the scene as the output. intersection Format is:
		Barycentric Coord is (a, b, c)=(S1, S2, S3)/S
		Result: float4 nearestIntersection = { a, b, c, distance} 
		where distance is t
	*/
    float MinDistance = MaxDistance;
	uint nearestIndex=-1; nearestIntersection.w=nearestIndex;  
	//before return, update distance t into nearest triangle index; 
	// nearestIndex=-1 means no intersection is fount 
	
    for (uint i = 0; i < (uint) triangles[0].w; i++)
    {
        float4 intersection = IntersectTriangle(i, origin, direction);
        float distance = intersection.w;
        if (distance < MinDistance)
        {
            nearestIntersection = intersection;
            nearestIndex = i;
            MinDistance = distance;
        }

    }
    nearestIntersection.w = nearestIndex;
    return nearestIntersection;
}

 // Interpolate color or position at an intersection using Barycentric coord
float3 Interpolate(float4 intersection, bool isColor)
{
	uint i=uint(intersection.w), i0=uint(triangles[i].x), i1=uint(triangles[i].y), i2=uint(triangles[i].z);
	return isColor?InterpolateVector(intersection.xyz, colors[i0].xyz, colors[i1].xyz, colors[i2].xyz):
	InterpolateVector(intersection.xyz, positions[i0].xyz, positions[i1].xyz, positions[i2].xyz);
}

float3 GetNormal(float4 intersection)  // Calculate normal direction at the intersection
{
	uint i=uint(intersection.w); uint i0=uint(triangles[i].x), i1=uint(triangles[i].y), i2=uint(triangles[i].z);
	float3 p0=positions[i0].xyz, p1=positions[i1].xyz, p2=positions[i2].xyz; return normalize(cross(p1-p0, p2-p0));
}

uint GetShadow(float3 position, float3 lightDirection)
{
	float3 o=position, d=lightDirection;
	float4 intersection=IntersectTriangles(o, d);
	return uint(intersection.w)==-1?0:1; 
	// intersection.w==-1: there is no intersection, it can see light at position p,  p is not on shadow
	// Otherwise; there is intersection with triangles and it can't see light at position p, p is on shadow
}

float3 ViewDirection(float3 inputPosition)
{
	float3 eyeCenter=viewPoint.xyz; float viewFocus=viewPoint.w;
	float3 focus=eyeCenter+viewFocus*forwardDirection.xyz;
	float3 rightOffset=inputPosition.x*rightDirection.xyz;
	float3 upOffset=inputPosition.y*upDirection.xyz;
	float3 viewCenter=focus+rightOffset+upOffset;
	return normalize(viewCenter-eyeCenter);
}

float4 GetColor(float4 intersection)  // 30 pts
{
	float3 color=float3(0, 0, 0);
	/*
		..........
	
		Implement the Direct Illumination
		Using Phong Reflection Model here

		..........
	*/
	if (intersection.w == -1) 
	{
		return float4(0, 0, 0, 1);
	}
	float3 colorAtPos = Interpolate(intersection, true);
	float3 Position = Interpolate(intersection, false);
	float3 L = normalize(lightPosition - Position);
	//float3 L = (lightPosition.x - intersection.x, lightPosition.y - intersection.y, lightPosition.z, intersection.z); //wrong way to calculate L
    float3 N = GetNormal(intersection);
	float shadow = lightColor.w*GetShadow(Position, L);
	//ignore v and r i thought i needed them
    //float3 V = (viewPoint.x - intersection.x, viewPoint.y - intersection.y, viewPoint.z, intersection.z);
    //float3 R = 2.0 * (dot(L, N)) * N - L;
    color = dot(L, N) /*+ dot(R, V)*/ ;
	return float4(lightColor.xyz*color*colorAtPos - shadow, 1);
}

float4 Environment(float4 intersection) // 30 pts
{
	float3 color=float3(0, 0, 0);
	/*
		..........
	
		Implement the Global Illumination
		Using Lambert Reflection Model here

		..........
	*/
	if (intersection.w == -1) return float4(1, 1, 1, 1);
	float3 N = GetNormal(intersection);
	float3 Position = Interpolate(intersection, false);
	int HalfCircle = 5;
	int Circle = HalfCircle * 2;
	float du = PI / (HalfCircle - 1);
	float dv = 2 * PI / (Circle - 1);
	float tolerance = 0.15;
	for (uint i = 0; i < HalfCircle; i++) 
	{
		for (uint j = 0; j < Circle; j++) 
		{
			float u = i * du;
			float v = j * dv;
			float x = sin(u) * cos(v);
			float y = cos(u);
			float z = sin(u) * sin(v);
			float3 rayDirection = float3(x, y, z);
			float intensity = dot(N, rayDirection);
			if (intensity >= tolerance) {
				intersection = IntersectTriangles(Position, rayDirection);
				if (uint(intersection.w) == -1) continue;
				float3 lightPosition = Interpolate(intersection, false);
				float lightDistance = distance(lightPosition, Position);
				float shadowdecay = 1.0 / (lightDistance * lightDistance + tolerance);
				color += GetColor(intersection) * intensity * shadowdecay;
			}
		}
	}
	return float4(color, 1);
}

float4 StylizedColor(float4 color) // 40 pts
{
	/*
		..........
	
		Implement a novel lighting model or 
		stylized rendering model as here, 
		this model has not been covered in leceture 

		..........
	*/
	color.x = (round(color.x* 5.0) ) / 10.0;
	color.y = (round(color.y* 5.0) ) / 10.0;
	color.z = (round(color.z* 5.0) ) / 10.0;
	return float4(color);
}


struct VS_Input
{
	float2 position : POSITION;
};

struct VS_Output
{
	float3 position : POSITION;
	float4 sv_position : SV_POSITION;
};

VS_Output VS_Main(VS_Input input)
{
	VS_Output output; output.position=float3(input.position, 0);
	output.sv_position=float4(output.position, 1); return output;
}

float4 ViewDirectionColor(float3 viewDirection)
{
	float r=dot(viewDirection, rightDirection.xyz);
	float g=dot(viewDirection, upDirection.xyz);
	float b=dot(viewDirection, forwardDirection.xyz);
	return float4((float2(r, g)+float2(1, 1))/2, b, 1);
}

float4 PS_Main(VS_Output output) : SV_TARGET
{
	float3 viewDirection=ViewDirection(output.position);  
	//return ViewDirectionColor(viewDirection); // for color testing purpose
	float4 intersection=IntersectTriangles(viewPoint.xyz, viewDirection);
	//return GetColor(intersection)  + Environment(intersection) * lightPosition.w;
	return StylizedColor(GetColor(intersection))+StylizedColor(Environment(intersection)) * lightPosition.w;
    //return GetColor(intersection);
}


	
