// Retorna a menor string lexicografica de s. Necessario my_hash() e
// lcp() longest common prefix - usar bb e myhash
string min_lex_rot(string s) {
  int t = s.size();
  precompute(s); // hashing
  s += s;
  int idx = 0;
  for (int i = 1; i < t; i++) {
    // tam do prefix comum
    int len = lcp(i, idx, t);
    if (s[i + len] < s[idx + len])
      idx = i;
  }
  return s.substr(idx, t);
}