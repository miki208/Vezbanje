theory kolokvijumi
imports Main

begin

thm notE
thm notI
thm conjI
thm conjE
thm conjunct1
thm conjunct2
thm disjI1
thm disjI2
thm disjE
thm classical
thm ccontr

(* 11. zadatak *)
lemma "(p \<and> q \<longrightarrow> r) \<longrightarrow> (p \<longrightarrow> (q \<longrightarrow> r))"
apply (rule impI)
apply (rule impI)
apply (rule impI)
apply (rule ccontr)
apply (erule impE)
apply (rule conjI)
apply assumption
apply assumption
apply (erule_tac ?P="r" in notE)
apply assumption
done

lemma "(p \<longrightarrow> (q \<longrightarrow> r)) \<longrightarrow> (p \<and> q \<longrightarrow> r)"
apply (rule impI)
apply (rule impI)
apply (erule conjE)
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule impE)
apply assumption
apply (erule_tac ?P="r" in notE)
apply assumption
done

(* 12. zadatak *)
lemma "(~B \<longrightarrow> (A \<longrightarrow> B)) \<and> (~B \<longrightarrow> (A \<or> B)) \<longrightarrow> B"
apply (rule impI)
apply (erule conjE)
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule impE)
apply assumption
apply (erule disjE)
apply (erule impE)
apply assumption
apply (erule notE)
apply assumption
apply (erule notE)
apply assumption
done

(* 13. zadatak *)
lemma "(~B \<longrightarrow> ~A) \<longrightarrow> ((B \<or> A) \<longrightarrow> B)"
apply (rule impI)
apply (rule impI)
apply (erule disjE)
apply assumption
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule_tac ?P="A" in notE)
apply assumption
done

(* 14. zadatak *)
lemma "~((p \<longrightarrow> q) \<and> (~r \<or> s)) \<longrightarrow> ((p \<and> ~q) \<or> (r \<and> ~s))"
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule conjI)
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule disjI1)
apply (rule conjI)
apply assumption
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
