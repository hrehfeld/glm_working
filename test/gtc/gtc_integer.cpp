///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2014 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2014-11-17
// Updated : 2014-11-17
// Licence : This source is under MIT licence
// File    : test/gtc/integer.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#define GLM_FORCE_INLINE
#include <glm/gtc/integer.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/vec1.hpp>
#include <glm/gtx/type_aligned.hpp>
#include <glm/vector_relational.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <ctime>
#include <cstdio>
#include <vector>

namespace log2_
{
	int test()
	{
		int Error = 0;

		int A0(glm::log2(10.f));
		glm::ivec1 B0(glm::log2(glm::vec1(10.f)));
		glm::ivec2 C0(glm::log2(glm::vec2(10.f)));
		glm::ivec3 D0(glm::log2(glm::vec3(10.f)));
		glm::ivec4 E0(glm::log2(glm::vec4(10.f)));

		int A1 = glm::log2(int(10.f));
		glm::ivec1 B1 = glm::log2(glm::ivec1(10.f));
		glm::ivec2 C1 = glm::log2(glm::ivec2(10.f));
		glm::ivec3 D1 = glm::log2(glm::ivec3(10.f));
		glm::ivec4 E1 = glm::log2(glm::ivec4(10.f));

		Error += A0 == A1 ? 0 : 1;
		Error += glm::all(glm::equal(B0, B1)) ? 0 : 1;
		Error += glm::all(glm::equal(C0, C1)) ? 0 : 1;
		Error += glm::all(glm::equal(D0, D1)) ? 0 : 1;
		Error += glm::all(glm::equal(E0, E1)) ? 0 : 1;

		return Error;
	}

	int perf()
	{
		int Error = 0;
		std::size_t const Count(100000000);

		{
			std::vector<int> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
				Result[i] = glm::log2(static_cast<int>(i));

			std::clock_t End = clock();

			printf("glm::log2<int>: %d clocks\n", End - Begin);
		}

		{
			std::vector<glm::ivec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
				Result[i] = glm::log2(glm::ivec4(i));

			std::clock_t End = clock();

			printf("glm::log2<ivec4>: %d clocks\n", End - Begin);
		}

#		if(GLM_ARCH != GLM_ARCH_PURE) && (GLM_COMPILER & (GLM_COMPILER_VC | GLM_COMPILER_APPLE_CLANG | GLM_COMPILER_LLVM))
		{
			std::vector<glm::ivec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
			{
				glm::tvec4<unsigned long, glm::defaultp> Tmp(glm::uninitialize);
				_BitScanReverse(&Tmp.x, i);
				_BitScanReverse(&Tmp.y, i);
				_BitScanReverse(&Tmp.z, i);
				_BitScanReverse(&Tmp.w, i);
				Result[i] = glm::ivec4(Tmp);
			}

			std::clock_t End = clock();

			printf("glm::log2<ivec4> inlined: %d clocks\n", End - Begin);
		}


		{
			std::vector<glm::tvec4<unsigned long, glm::defaultp> > Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
			{
				_BitScanReverse(&Result[i].x, i);
				_BitScanReverse(&Result[i].y, i);
				_BitScanReverse(&Result[i].z, i);
				_BitScanReverse(&Result[i].w, i);
			}

			std::clock_t End = clock();

			printf("glm::log2<ivec4> inlined no cast: %d clocks\n", End - Begin);
		}


		{
			std::vector<glm::ivec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
			{
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].x), i);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].y), i);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].z), i);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].w), i);
			}

			std::clock_t End = clock();

			printf("glm::log2<ivec4> reinterpret: %d clocks\n", End - Begin);
		}
#		endif//GLM_ARCH != GLM_ARCH_PURE

		{
			std::vector<float> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
				Result[i] = glm::log2(static_cast<float>(i));

			std::clock_t End = clock();

			printf("glm::log2<float>: %d clocks\n", End - Begin);
		}

		{
			std::vector<glm::vec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
				Result[i] = glm::log2(glm::vec4(i));

			std::clock_t End = clock();

			printf("glm::log2<vec4>: %d clocks\n", End - Begin);
		}

		return Error;
	}
}//namespace log2_


int main()
{
	int Error(0);

	Error += ::log2_::test();

#	ifdef GLM_TEST_ENABLE_PERF
		Error += ::log2_::perf();
#	endif

	return Error;
}
