#pragma once
#include"../oakpch.h"


namespace Oak {

	enum class ShaderDataType :uint8_t {
		None, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return sizeof(bool);
		}
		OAK_CORE_ASSERT(false, "Unknown shader data type");
		return 0;
	}


	

	struct BufferLayoutElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		uint32_t Count;
		uint32_t GLType;
		bool Normalized;

		BufferLayoutElement(ShaderDataType type,const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Count(GetComponentCount()), GLType(GetTypeToGLType(type)), Normalized(normalized),Offset(0) {}
		
		uint32_t GetComponentCount() const {
			switch (Type) {
			case ShaderDataType::Float:	return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
			}
			OAK_CORE_ASSERT(false, "Unknown ShaderDataType !");
			return 0;
		}

		uint32_t GetTypeToGLType(ShaderDataType type) const {
			switch (type) {
			case ShaderDataType::Float:		return 0x1406;				//GL_FLOAT == 0x1406
			case ShaderDataType::Float2:	return 0x1406;
			case ShaderDataType::Float3:	return 0x1406;
			case ShaderDataType::Float4:	return 0x1406;
			case ShaderDataType::Int:		return 0x1404;				//GL_INT == 0x1404
			case ShaderDataType::Int2:		return 0x1404;
			case ShaderDataType::Int3:		return 0x1404;
			case ShaderDataType::Int4:		return 0x1404;
			case ShaderDataType::Mat3:		return 0x1406;
			case ShaderDataType::Mat4:		return 0x1406;
			case ShaderDataType::Bool:		return 0x8B56;				// GL_BOOL == 0x8B56
			}
			OAK_CORE_ASSERT(false, "Unknown ShaderDataType !");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
			: m_Elements(elements) {
			CalculateOffsetsAndStride();
		}
		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }

		inline std::vector<BufferLayoutElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferLayoutElement>::iterator end() { return m_Elements.end(); }

	private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride = 0;

		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	};

	//////////////////////////////////////////////////////
	/////////////////// VertexBuffer /////////////////////
	//////////////////////////////////////////////////////
	class VertexBuffer
	{
	public:
		virtual  ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	//////////////////////////////////////////////////////
	/////////////////// IndexBuffer //////////////////////
	//////////////////////////////////////////////////////
	class IndexBuffer
	{
	public:
		virtual  ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};


}