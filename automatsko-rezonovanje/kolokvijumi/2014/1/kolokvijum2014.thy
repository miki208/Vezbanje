theory kolokvijum2014
imports Main
begin

thm notI
thm notE
thm conjunct1
thm conjunct2
thm conjI
thm conjE
thm disjI1
thm disjI2
thm disjE
thm impI
thm impE
thm classical
thm ccontr

lemma "\<not>((P --> Q) \<and> (\<not>R \<or> S)) --> ((P \<and> \<not>Q) \<or> (R \<and> \<not>S))"
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule conjI)
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule disjI1)
apply (erule conjI)
apply assumption
apply (rule ccontr)
apply (erule notE)
apply (rule disjI2)
apply (rule conjI)
apply (rule ccontr)
apply (erule notE)
apply (rule disjI1)
apply assumption
apply (rule notI)
apply (erule notE)
apply (rule disjI2)
apply assumption
done
end