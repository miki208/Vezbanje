theory kolokvijum2016
imports Main
begin

thm notI
thm notE
thm conjunct1
thm conjunct2
thm conjE
thm conjI
thm disjI1
thm disjI2
thm disjE
thm impI
thm impE
thm classical
thm ccontr

lemma "(((p --> q) \<or> (\<not>r \<and> s)) \<and> (s --> ((p \<and> \<not>q) \<or> r)) --> (p --> q)) --> ((\<not>r \<and> s) --> (p --> q))"
apply (rule impI)
apply (rule impI)
apply (rule impI)
apply (rule ccontr)
apply (erule impE)
apply (rule conjI)
apply (rule disjI2)
apply assumption
apply (rule impI)
apply (rule disjI1)
apply (rule conjI)
apply assumption
apply assumption
apply (erule impE)
apply assumption
apply (erule_tac ?P="q" in notE)
apply assumption
done
end