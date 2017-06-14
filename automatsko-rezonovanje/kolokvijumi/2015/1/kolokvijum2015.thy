theory kolokvijum2015
imports Main
begin

thm notI
thm notE
thm conjunct1
thm conjunct2
thm conjE
thm conjI
thm disjE
thm disjI1
thm disjI2
thm impI
thm impE
thm classical
thm ccontr

lemma "(((B \<and> \<not>C) \<longrightarrow> (\<not>A \<or> (B \<longrightarrow> C))) \<and> (\<not>(B \<longrightarrow> C) \<longrightarrow> (A \<or> \<not>B \<or> C))) \<longrightarrow> (B \<longrightarrow> C)"
apply (rule impI)
apply (rule impI)
apply (erule conjE)
apply (rule ccontr)
apply (erule impE)
apply (rule conjI)
apply assumption
apply assumption
apply (erule impE)
apply (rule notI)
apply (erule impE)
apply assumption
apply (erule_tac ?P="C" in notE)
apply assumption
apply (erule disjE)
apply (erule disjE)
apply (erule_tac ?P="A" in notE)
apply assumption
apply (erule disjE)
apply (erule_tac ?P="B" in notE)
apply assumption
apply (erule_tac ?P="C" in notE)
apply assumption
apply (erule impE)
apply assumption
apply (erule_tac ?P="C" in notE)
apply assumption
done

end