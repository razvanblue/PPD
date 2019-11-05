public class BigNumber
{
    public List<byte> digits = new ArrayList<>();
    public int size;
    static public final int MAX_SIZE = 50;

    public BigNumber() {
        size = 0;
    }
    public BigNumber(int size) {
        if (size > MAX_SIZE) throw new Exception("Size too big!");
        this.size = size;
    }
    public BigNumber(byte[] arr) {
        if (size > MAX_SIZE) throw new Exception("Size too big!");
        for (byte e : arr)
            digits.push(e);
        this.size = size;
    }

    public BigNumber multiplyWithDigit(byte digit);{
        
        if(digit > 9) throw new Exception(digit + " nu este cifra!");
            
        BigNumber ret = new BigNumber(size + 1);
        
        byte carry = 0;
        for(int i = 0; i < size; i++)
        {
            ret.digits[i] = (this.digits[i] * digit + carry) % 10;
            carry = (this.digits[i] * digit + carry) / 10;
        }
        
        if (carry == 0) ret.size = size;
        else ret[size] = carry;
        return ret;
    }
    
    public BigNumber multiplyWithDigitParallel(byte digit, int tc) {
        if(digit > 9) throw new Exception(digit + " nu este cifra!");
        
        int tlen = size / tc;                // length of a thread's working range
        int remainder = size % tc;              // remainder to be distributed
        BigNumber ret = new BigNumber(size + 1);
        
        List<Thread> threads = new ArrayList<>(tc);
        
        //Create threads
        int i, start = 0;
        int end = (remainder == 0) ? tlen : tlen + 1;
        for (i = 0; i < remainder; i++)
        {
            threads.add(new MultiplicationThread(ret.digits, digit, start, end));
            start += tlen + 1;
            end += tlen + 1;
        }
        for (; i < tc; i++)
        {
            threads.add(new MultiplicationThread(ret.digits, digit, start, end));
            start += tlen;
            end += tlen;
        }
        for (Thread t : threads)
            t.start();
        for (Thread t : threads)
            t.join();
        //TODO: Merge carries
        
        if (ret.digits[] == 0) ret.size = size;
        else ret.digits[size] = carry;
        
        return ret;
    }
    
    public BigNumber multiplySeq(BigNumber other) {
        boolean comp = (size < other.size);
        int minlen = comp ? size : other.size;
        BigNumber bigger = comp ? other : this;
        BigNumber smaller = comp ? this : other;
        
        BigNumber ret = new BigNumber();
        
        for(int i = 0; i < minlen; i++)
        {
            ret = ret.addSeq(bigger.MultiplyWithDigit(smaller.digits[i]));
        }
        return ret;
    }

    private static void multiplyRangeWithDigit(byte[] arr, byte digit, int start, int end) {
        uint8_t carry = 0;
        for (int i = start; i < end; i++)
        {
            arr[i] = (arr[i] * digit + carry) % 10;
            carry = (arr[i] * digit + carry) / 10;
        }
        carries[end] = carry;
    }
}

