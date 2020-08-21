pub mod sorting {
    pub enum SCENT{
        ASCENT,
        DESCENT,
    }
    pub fn swap<T: Clone>(i: &mut T, j: &mut T) {
        let temp: T = i.clone();
        *i = j.clone();
        *j = temp;

    }
    // direction: 0: ascent 1: 
    pub fn bubble_sort(arr: &mut [i32], scent: SCENT) {

    }
}