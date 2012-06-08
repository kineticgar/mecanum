#ifndef BYTEARRAY_H
#define BYTEARRAY_H


class ByteArray
{
public:
	ByteArray() : length(0) { }

	ByteArray(unsigned char *bytes, unsigned char length) : bytes(bytes), length(length) { }

	ByteArray(const ByteArray &other) : bytes(other.bytes), length(other.length) { }

	ByteArray &operator=(const ByteArray &src);

	~ByteArray() { }

	bool operator==(const ByteArray &other) const;

	unsigned char &operator[](unsigned char i) const { return bytes[i]; }

	/**
	 * Decrease the size of the buffer. The byte array is shifted to match the
	 * decreased size (bytes are popped off the front of the array).
	 */
	ByteArray &operator>>(unsigned char i) { Shift(i); return *this; }

	/**
	 * Increase the size of the buffer. This does NOT shift the byte array.
	 * Additional padding is pushed onto the back. Ensure that the buffer is
	 * large enough to handle the increased size (I know yo mamma is).
	 *
	 * The maximum size is 255 (0xFF); if i pushes the size over the limit,
	 * the length is clipped at 255.
	 */
	ByteArray &operator<<(unsigned char i);

	void Shift(unsigned char i);

	/**
	 * Buffer's length equals this object's Length() plus one.
	 */
	void PrependLength(unsigned char *buffer) const;

	unsigned char Length() const { return length; }
	void SetLength(unsigned char newLength) { length = newLength; }

	/**
	 * Precondition: buffer's size is at least 4. To achieve compatibility with
	 * 8-bit processors, only the lowest 4 bytes of n are serialized.
	 * Postcondition: buffer contains n in big endian format.
	 */
	static void Serialize(unsigned long n, unsigned char *buffer);

	/**
	 * The pre- and post-conditions are similar to above, but probably reversed.
	 */
	static void Deserialize(const unsigned char *buffer, unsigned long &n);

private:
	unsigned char *bytes;
	unsigned char length;
};

#endif // BYTEARRAY_H
