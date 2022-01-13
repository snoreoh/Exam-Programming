template <typename Iterator1, typename Iterator2>
Iterator2 merge( Iterator1 first1, Iterator1 last1, Iterator1 first2, Iterator1 last2,
Iterator2 output ) {
    Iterator2 tmp = output;
    while ((first1 != last1) && (first2 != last2))
    {
        if (first1 == last1) {
            while (first2 != last2) {
                *tmp = *first2;
                first2++;
                tmp++;
            }
        } else if (first2 == last2) {
            while (first1 != last1) {
                *tmp = *first1;
                first1++;
                tmp++;
            }
        } else {
            if (*first1 <= *first2) {
                *tmp = *first1;
                first1++;
            } else {
                *tmp = *first2;
                first2++;
            }
            tmp++;
        }
    }
    return output;
}
